#include <solitaire2/gamestate/foundation.hpp>
#include <solitaire2/gamestate/stock.hpp>
#include <solitaire2/gamestate/tableau.hpp>

using namespace solitaire2;

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
GameState<CardType, GameDeckType, FoundationType, TableauType>::GameState() : gamedeck_(), foundation_(), tableau_() {

    Deck<CardType> deck;
    deck.shuffle();
    initialize_from_deck(deck);
}

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
void GameState<CardType, GameDeckType, FoundationType, TableauType>::initialize_from_deck(const Deck<CardType>& deck) {
    uint8_t card_index=0;
    std::vector<std::vector<CardType>> tableau_cards;
    tableau_cards.resize(7);
    for (uint8_t pile=0; pile<7; ++pile){
        for(uint8_t card=0; card<=pile; ++card){
            tableau_cards[pile].push_back(deck[card_index]);
            ++card_index;
        }
    }
    gamedeck_ = GameDeckType(deck.begin()+card_index, deck.end());
}

template class GameState<BasicCard, BasicGameDeck<BasicCard>, BasicFoundation, BasicTableau<BasicCard>>;