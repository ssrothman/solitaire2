#ifndef SOLITAIRE2_GAMESTATE_BOARD_HPP
#define SOLITAIRE2_GAMESTATE_BOARD_HPP

#include <solitaire2/cards.hpp>

/**
 * The `game state` of the solitaire game consists of the following components:
 * - A deck of cards (the `gamedeck`), which is split into the `stock` and `waste` piles
 * - A set of four `foundation` piles, one for each suit, where cards are played in ascending order from Ace to King
 * - A set of seven `tableau` piles, where cards are played in descending order and alternating colors
 *        
 */


namespace solitaire2 {

template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
class GameState {
public:
    GameState();
    GameState(const Deck<CardType>& deck);

    const GameDeckType& gamedeck() const noexcept { return gamedeck_; }
    const FoundationType& foundation() const noexcept { return foundation_; }
    const TableauType& tableau() const noexcept { return tableau_; }

private:
    void initialize_from_deck(const Deck<CardType>& deck);

    GameDeckType gamedeck_;
    FoundationType foundation_;
    TableauType tableau_;

}; // end class GameState

}; // end namespace solitaire2

#endif