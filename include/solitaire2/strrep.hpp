#ifndef SOLITAIRE2_STRREP_HPP
#define SOLITAIRE2_STRREP_HPP

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

    std::string to_string(Suit suit) {
        return suit_chars[static_cast<size_t>(suit)];
    }
    std::string to_string(Rank rank) {
        return rank_chars[static_cast<size_t>(rank)];
    }

    template <typename CardType>
    std::string to_string(const CardType& card) {
        return to_string(card.rank()) + to_string(card.suit());
    }

    template <typename CardType>
    void print_card(const CardType& card) {
        // get the color right, in addition to printing the card
        if (card.is_red()) {
            std::cout << TERM_RED;
        } else {
            std::cout << TERM_BLUE;
        }
        std::cout << to_string(card) << std::endl;
        std::cout << TERM_RESET;
    }
};

#endif