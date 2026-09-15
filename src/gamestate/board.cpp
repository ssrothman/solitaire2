#include <solitaire2/gamestate/foundation.hpp>
#include <solitaire2/gamestate/gamedeck.hpp>
#include <solitaire2/gamestate/tableau.hpp>
#include <solitaire2/gamestate/board.hpp>

using namespace solitaire2;

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
GameBoard<CardType, GameDeckType, FoundationType, TableauType>::GameBoard(bool shuffle) : gamedeck_(), foundation_(), tableau_() {

    Deck<CardType> deck;
    if (shuffle) {
        deck.shuffle();
    }
    initialize_from_deck(deck);
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::initialize_from_deck(Deck<CardType>& deck) {
    uint8_t card_index=0;
    std::vector<std::vector<CardType>> tableau_cards;
    tableau_cards.resize(7);
    for (uint8_t pile=0; pile<7; ++pile){
        for(uint8_t card=0; card<=pile; ++card){
            tableau_cards[pile].push_back(deck.pick(card_index));
            ++card_index;
        }
    }
    tableau_ = TableauType(tableau_cards);
    gamedeck_ = GameDeckType(deck.begin()+card_index, deck.end());
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::stock_mill(){
    gamedeck_.mill();
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::stock_reset(){
    gamedeck_.reset_draw();
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::waste_to_tableau(uint8_t target){
    tableau_.move_onto({gamedeck_.draw_from_waste()}, target);
}


template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::waste_to_foundation(){
    foundation_.play_onto(gamedeck_.draw_from_waste().suit());
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::tableau_to_tableau(uint8_t source, uint8_t target){
    tableau_.move_onto({tableau_.take_from(1, source)}, target);
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameBoard<CardType, GameDeckType, FoundationType, TableauType>::tableau_to_foundation(uint8_t source){
    foundation_.play_onto(tableau_.take_from(1, source)[0].suit());
}

template class GameBoard<BasicCard, BasicGameDeck<BasicCard>, BasicFoundation, BasicTableau<BasicCard>>;