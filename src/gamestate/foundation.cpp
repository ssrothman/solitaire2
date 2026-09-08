#include <solitaire2/gamestate/foundation.hpp>

solitaire2::Rank solitaire2::BasicFoundation::at(solitaire2::Suit suit) const{
    if (static_cast<uint8_t>(suit) >= 4){
        throw std::out_of_range("Suit out of range in BasicFoundation::at()");
    } else {
        return piles_[static_cast<uint8_t>(suit)];
    }
}

void solitaire2::BasicFoundation::play_onto(solitaire2::Suit suit){
    if (static_cast<uint8_t>(suit) >= 4){
        throw std::out_of_range("Suit out of range in BasicFoundation::at()");
    } else {
        ++(piles_[static_cast<uint8_t>(suit)]);
    }
}