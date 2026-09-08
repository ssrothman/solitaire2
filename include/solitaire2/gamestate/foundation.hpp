#ifndef SOLITAIRE2_GAMESTATE_FOUNDATION_HPP
#define SOLITAIRE2_GAMESTATE_FOUNDATION_HPP

#include <solitaire2/cards.hpp>
#include <array>

namespace solitaire2 { 
/**
    Foundation piles
    Naive implementation is just the rank of the top card
*/

class BasicFoundation {
public:
    BasicFoundation() : piles_({solitaire2::Rank::Undef, solitaire2::Rank::Undef, solitaire2::Rank::Undef, solitaire2::Rank::Undef}) {}

    // inspection
    solitaire2::Rank at(solitaire2::Suit suit);
    
    // update
    void play_onto(solitaire2::Suit suit);

private:
    std::array<solitaire2::Rank, 4> piles_;

}; //end class BasicFoundation
    
};//

#endif