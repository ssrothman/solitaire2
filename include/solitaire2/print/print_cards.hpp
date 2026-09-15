#ifndef SOLITAIRE2_UTIL_PRINT_CARDS_HPP
#define SOLITAIRE2_UTIL_PRINT_CARDS_HPP

#include <stdio.h>
#include <iostream>
#include <string>

/*
 * Here we implement to_string() for suits, ranks, and cards. 
*/
#include <solitaire2/cards.hpp>

namespace solitaire2 {
    constexpr std::array<const char *, 4> suit_chars = {"♥", "♦", "♣", "♠"};
    constexpr std::array<const char *, 14> rank_chars = {"?", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    constexpr std::string TERM_RED = "\033[31m";
    constexpr std::string TERM_BLUE = "\033[34m";
    constexpr std::string TERM_RESET = "\033[0m";

    inline std::ostream& operator<< (std::ostream& outs, const Suit& suit){
        return outs << suit_chars[static_cast<size_t>(suit)];
    }

    inline std::ostream& operator<< (std::ostream& outs, const Rank& rank){
        return outs << rank_chars[static_cast<size_t>(rank)];
    }

    template <typename CardType>
    inline std::ostream& streamcard(std::ostream& outs, const CardType& card){
        if (card.is_red()) {
            outs << TERM_RED;
        } else {
            outs << TERM_BLUE;
        }

        outs << rank_chars[static_cast<size_t>(card.rank())] << suit_chars[static_cast<size_t>(card.suit())];

        outs << TERM_RESET;
        return outs;
    }
    inline std::ostream& operator<< (std::ostream& outs, const BasicCard& card){
        return streamcard(outs, card);
    }
    inline std::ostream& operator<< (std::ostream& outs, const PackedCard& card){
        return streamcard(outs, card);
    }

    template <typename CardType>
    inline void print_card(const CardType& card) {
        // get the color right, in addition to printing the card
        std::cout << card;
    }
};

#endif