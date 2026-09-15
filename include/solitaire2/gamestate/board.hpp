#ifndef SOLITAIRE2_GAMESTATE_BOARD_HPP
#define SOLITAIRE2_GAMESTATE_BOARD_HPP

#include <solitaire2/cards.hpp>
#include <solitaire2/moves.hpp>

#include <solitaire2/gamestate/gamedeck.hpp>
#include <solitaire2/gamestate/tableau.hpp>
#include <solitaire2/gamestate/foundation.hpp>

#include <iostream>

/**
 * The `game state` of the solitaire game consists of the following components:
 * - A deck of cards (the `gamedeck`), which is split into the `stock` and `waste` piles
 * - A set of four `foundation` piles, one for each suit, where cards are played in ascending order from Ace to King
 * - A set of seven `tableau` piles, where cards are played in descending order and alternating colors
 *        
 */


namespace solitaire2 {

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
class GameBoard {
public:
    GameBoard(bool shuffle=true, size_t seed=0);
    GameBoard(const Deck<CardType>& deck);

    const GameDeckType& gamedeck() const noexcept { return gamedeck_; }
    const FoundationType& foundation() const noexcept { return foundation_; }
    const TableauType& tableau() const noexcept { return tableau_; }

    template <typename MoveType>
    bool is_valid_move(const MoveType& move){
        switch(move.type()){
            case static_cast<uint8_t>(MoveKind::WasteToStock):
                return gamedeck_.stock_empty() && !gamedeck_.waste_empty();

            case static_cast<uint8_t>(MoveKind::StockToWaste):
                return !gamedeck_.stock_empty();

            case static_cast<uint8_t>(MoveKind::WasteToTableau):
                return tableau_.num_face_up(move.target_index()) == 0 ? gamedeck_.top_of_waste().rank() == Rank::King : gamedeck_.top_of_waste().can_play_below(tableau_.face_up(move.target_index())[tableau_.num_face_up(move.target_index()) - 1]);

            case static_cast<uint8_t>(MoveKind::WasteToFoundation):
                return static_cast<uint8_t>(gamedeck_.top_of_waste().rank()) == static_cast<uint8_t>(foundation_.at(gamedeck_.top_of_waste().suit())) + 1;

            case static_cast<uint8_t>(MoveKind::TableauToTableau):

                if (tableau_.num_face_up(move.target_index()) == 0){
                    return move.amount() <= tableau_.face_up(move.source_index()).size() && tableau_.face_up(move.source_index())[tableau_.face_up(move.source_index()).size() - move.amount()].rank() == Rank::King;       
                } else {
                    return move.amount() <= tableau_.face_up(move.source_index()).size() && tableau_.face_up(move.source_index())[tableau_.face_up(move.source_index()).size() - move.amount()].can_play_below(tableau_.face_up(move.target_index())[tableau_.num_face_up(move.target_index()) - 1]);
                }

            case static_cast<uint8_t>(MoveKind::TableauToFoundation):
                return !tableau_.face_up(move.source_index()).empty() && static_cast<uint8_t>(tableau_.face_up(move.source_index())[tableau_.face_up(move.source_index()).size() - 1].rank()) == static_cast<uint8_t>(foundation_.at(tableau_.face_up(move.source_index())[tableau_.face_up(move.source_index()).size() - 1].suit())) + 1;
            
            default:
                std::cerr << "WARNING: INVALID MOVE TYPE" << std::endl;
                return false;
        }
    }

    template <typename MoveType>
    void apply_move(const MoveType& move){
        switch(move.type()){
            case static_cast<uint8_t>(MoveKind::WasteToStock):
                stock_reset();
                break;
            case static_cast<uint8_t>(MoveKind::StockToWaste):
                stock_mill();
                break;
            case static_cast<uint8_t>(MoveKind::WasteToTableau):
                waste_to_tableau(move.target_index());
                break;
            case static_cast<uint8_t>(MoveKind::WasteToFoundation):
                waste_to_foundation();
                break;
            case static_cast<uint8_t>(MoveKind::TableauToTableau):
                tableau_to_tableau(move.source_index(), move.target_index(), move.amount());
                break;
            case static_cast<uint8_t>(MoveKind::TableauToFoundation):
                tableau_to_foundation(move.source_index());
                break;
        }
    }

    template <typename MoveType>
    GameBoard<CardType, GameDeckType, FoundationType, TableauType> apply_move_immutable(const MoveType& move) const{
        GameBoard<CardType, GameDeckType, FoundationType, TableauType> result(*this);
        result.apply_move(move);
    }

private:
    void initialize_from_deck(Deck<CardType>& deck);

    void stock_mill();
    void stock_reset();
    void waste_to_tableau(uint8_t target);
    void waste_to_foundation();
    void tableau_to_tableau(uint8_t source, uint8_t target, uint8_t amount);
    void tableau_to_foundation(uint8_t source);

    GameDeckType gamedeck_;
    FoundationType foundation_;
    TableauType tableau_;

    

}; // end class GameBoard

using BasicGameBoard = GameBoard<BasicCard, BasicGameDeck<BasicCard>, BasicFoundation, BasicTableau<BasicCard>>;

}; // end namespace solitaire2

#endif