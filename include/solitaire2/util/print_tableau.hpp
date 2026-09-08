#ifndef SOLITAIRE2_UTIL_PRINT_TABLEAU_HPP
#define SOLITAIRE2_UTIL_PRINT_TABLEAU_HPP

#include <stdio.h>
#include <iostream>
#include <string>

#include "print_cards.hpp"
#include <solitaire2/gamestate/tableau.hpp>
#include <solitaire2/cards.hpp>

namespace solitaire2 {


template <typename TableauType>
std::ostream& tableaustream (std::ostream& outs, const TableauType& tableau){
    for (uint8_t pile=0; pile<7; ++pile){
        outs << static_cast<int>(pile) << ": ";
        for (const auto& card : tableau.face_up(pile)){
            outs << card << " ";
        }
        outs << "\n";
    }
    return outs;
}

std::ostream& operator<< (std::ostream& outs, const BasicTableau<BasicCard>& tableau){
    return tableaustream(outs, tableau);
}
std::ostream& operator<< (std::ostream& outs, const BasicTableau<PackedCard>& tableau){
    return tableaustream(outs, tableau);
}

template <typename TableauType>
void print_tableau(const TableauType& tableau) {
    std::cout << tableau;
}

}; // end namespace solitaire2

#endif