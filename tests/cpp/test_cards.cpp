#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>

TEST_CASE("Basic functionality of BasicCard") {
    solitaire2::BasicCard card(solitaire2::Suit::Hearts, solitaire2::Rank::Ace);
    
    REQUIRE(card.suit() == solitaire2::Suit::Hearts);
    REQUIRE(card.rank() == solitaire2::Rank::Ace);
    
    REQUIRE(card.is_red());
    REQUIRE(!card.is_black());
    REQUIRE(card.is_valid());

    solitaire2::BasicCard invalid_card(solitaire2::Suit::Hearts, solitaire2::Rank::Undef);
    REQUIRE(!invalid_card.is_valid());

    solitaire2::BasicCard card2(solitaire2::Suit::Spades, solitaire2::Rank::Six);
    REQUIRE(card2.is_black());
    REQUIRE(!card2.is_red());
    REQUIRE(card2.is_valid());

    REQUIRE(card.can_play_below(card2) == false);
    solitaire2::BasicCard card3(solitaire2::Suit::Diamonds, solitaire2::Rank::Five);
    REQUIRE(card3.can_play_below(card2) == true);   
    REQUIRE(card2.can_play_below(card3) == false);
}


TEST_CASE("Basic functionality of PackedCard") {
    solitaire2::PackedCard card(solitaire2::Suit::Diamonds, solitaire2::Rank::Three);
    REQUIRE(card.suit() == solitaire2::Suit::Diamonds);
    REQUIRE(card.rank() == solitaire2::Rank::Three);
    REQUIRE(card.is_red());
    REQUIRE(!card.is_black());
    REQUIRE(card.is_valid());

    solitaire2::PackedCard invalid_card(solitaire2::Suit::Hearts, solitaire2::Rank::Undef);
    REQUIRE(!invalid_card.is_valid());

    solitaire2::PackedCard card2(solitaire2::Suit::Clubs, solitaire2::Rank::Nine);
    REQUIRE(card2.is_black());
    REQUIRE(!card2.is_red());
    REQUIRE(card2.is_valid());

    REQUIRE(card.can_play_below(card2) == false);
    solitaire2::PackedCard card3(solitaire2::Suit::Hearts, solitaire2::Rank::Eight);
    REQUIRE(card3.can_play_below(card2) == true);   
    REQUIRE(card2.can_play_below(card3) == false);
}