#ifndef SOLITAIRE2_UTIL_PRINT_GAMEDECK_HPP
#define SOLITAIRE2_UTIL_PRINT_GAMEDECK_HPP

#include <solitaire2/gamestate/gamedeck.hpp>
#include <solitaire2/cards.hpp>

namespace solitaire2 {

template <typename GameDeckType>
std::ostream& gamedeckstream(std::ostream& outs, const GameDeckType& gamedeck){
    outs << "[" << static_cast<int>(gamedeck.stock_size()) << "]  ";
    if (!gamedeck.waste_empty()){
        outs << gamedeck.top_of_waste();
    } else {
        outs << "  ";
    }
    return outs;
}

std::ostream& operator<<(std::ostream& outs, const BasicGameDeck<BasicCard>& gamedeck){
    return gamedeckstream(outs, gamedeck);
}
std::ostream& operator<<(std::ostream& outs, const BasicGameDeck<PackedCard>& gamedeck){
    return gamedeckstream(outs, gamedeck);
}

}; //end namespace solitaire2

#endif