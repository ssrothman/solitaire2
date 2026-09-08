#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/gamestate/foundation.hpp>
#include <solitaire2/prints.hpp>

template <typename FoundationType>
void test_foundation() {
    FoundationType foundation;

    // in initial state, all foundation piles should be empty (rank zero)
    for (uint8_t i=0; i<4; ++i){
        REQUIRE(foundation.at(static_cast<solitaire2::Suit>(i)) == solitaire2::Rank::Undef);
    }

    //foundation.at(i>4) should throw
    REQUIRE_THROWS_AS(foundation.at(static_cast<solitaire2::Suit>(4)), std::out_of_range);
    REQUIRE_THROWS_AS(foundation.at(static_cast<solitaire2::Suit>(15)), std::out_of_range);

    // play up the ace of hearts
    foundation.play_onto(solitaire2::Suit::Hearts);

    REQUIRE(foundation.at(solitaire2::Suit::Hearts) == solitaire2::Rank::Ace);
    REQUIRE(foundation.at(solitaire2::Suit::Diamonds) == solitaire2::Rank::Undef);
    REQUIRE(foundation.at(solitaire2::Suit::Spades) == solitaire2::Rank::Undef);
    REQUIRE(foundation.at(solitaire2::Suit::Clubs) == solitaire2::Rank::Undef);

    // play up the ace through three of spades
    foundation.play_onto(solitaire2::Suit::Spades);
    foundation.play_onto(solitaire2::Suit::Spades);
    foundation.play_onto(solitaire2::Suit::Spades);

    REQUIRE(foundation.at(solitaire2::Suit::Hearts) == solitaire2::Rank::Ace);
    REQUIRE(foundation.at(solitaire2::Suit::Diamonds) == solitaire2::Rank::Undef);
    REQUIRE(foundation.at(solitaire2::Suit::Spades) == solitaire2::Rank::Three);
    REQUIRE(foundation.at(solitaire2::Suit::Clubs) == solitaire2::Rank::Undef);

    // play the two of hearts
    foundation.play_onto(solitaire2::Suit::Hearts);

    REQUIRE(foundation.at(solitaire2::Suit::Hearts) == solitaire2::Rank::Two);
    REQUIRE(foundation.at(solitaire2::Suit::Diamonds) == solitaire2::Rank::Undef);
    REQUIRE(foundation.at(solitaire2::Suit::Spades) == solitaire2::Rank::Three);
    REQUIRE(foundation.at(solitaire2::Suit::Clubs) == solitaire2::Rank::Undef);
}

TEST_CASE("BasicFoundation functionality"){
    test_foundation<solitaire2::BasicFoundation>();
}
