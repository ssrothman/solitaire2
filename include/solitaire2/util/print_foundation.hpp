#ifndef SOLITAIRE2_UTIL_PRINT_FOUNDATION_HPP
#define SOLITAIRE2_UTIL_PRINT_FOUNDATION_HPP

#include <solitaire2/gamestate/foundation.hpp>

namespace solitaire2{

template <typename FoundationType>
std::ostream& foundationstream (std::ostream& outs, const FoundationType& foundation){
    for (uint8_t suit=0; suit<4; ++suit){
        Suit suit_enum = static_cast<Suit>(suit);
        Rank rank = foundation.at(suit_enum);
        if (rank == Rank::Undef) {
            outs << "-- ";
        } else {
            outs << BasicCard(suit_enum, rank) << " ";
        }
    }
    return outs;
}

std::ostream& operator<< (std::ostream& outs, const BasicFoundation& foundation){
    return foundationstream(outs, foundation);
}

}; //end namespace solitaire2

#endif