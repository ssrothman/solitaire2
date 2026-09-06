#ifndef SOLITAIRE2_GAMESTATE_BOARD_HPP
#define SOLITAIRE2_GAMESTATE_BOARD_HPP

#include <solitaire2/cards.hpp>

/**
 * The `game state` of the solitaire game consists of the following components:
 * - A deck of cards, which is split into the `draw` and `waste` piles
 * - A set of four `foundation` piles, one for each suit, where cards are played in ascending order from Ace to King
 * - A set of seven `tableau` piles, where cards are played in descending order and alternating colors
 *        
 */

namespace solitaire2 {

template <typename CardType>
class GameState {

}; // end class GameState

}; // end namespace solitaire2

#endif