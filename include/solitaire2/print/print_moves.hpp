#ifndef SOLITAIRE2_PRINT_PRINT_MOVES_HPP
#define SOLITAIRE2_PRINT_PRINT_MOVES_HPP

#include <iostream>
#include <solitaire2/move_notation.hpp>
#include <solitaire2/moves.hpp>

namespace solitaire2{

template <typename MoveType>
inline std::ostream& movestream (std::ostream& outs, const MoveType& move){
    outs << move_to_notation(move);
    return outs;
} 

inline std::ostream& operator<< (std::ostream& outs, const BasicMove& move){
    return movestream(outs, move);
}

inline std::ostream& operator<< (std::ostream& outs, const PackedMove& move){
    return movestream(outs, move);
}


};

#endif