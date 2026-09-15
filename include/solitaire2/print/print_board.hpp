#ifndef SOLITAIRE2_UTIL_PRINT_BOARD_HPP
#define SOLITAIRE2_UTIL_PRINT_BOARD_HPP

#include <iostream>
#include <solitaire2/gamestate/board.hpp>

namespace solitaire2 {
    template <typename CardType, typename GameDeckType, typename FoundationType, typename TableauType>
    inline std::ostream& operator<<(std::ostream& outs, const GameBoard<CardType, GameDeckType, FoundationType, TableauType>& board){
        outs << board.foundation() << std::endl;
        outs << std::endl;
        outs << board.tableau() << std::endl;
        outs << std::endl;
        outs << board.gamedeck() << std::endl;

        return outs;
    }
};

#endif