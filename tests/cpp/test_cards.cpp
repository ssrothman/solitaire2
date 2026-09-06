#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/strrep.hpp>

template <typename CardType>
void test_card_functionality(){
    CardType card(solitaire2::Suit::Hearts, solitaire2::Rank::Ace);
    
    REQUIRE(card.suit() == solitaire2::Suit::Hearts);
    REQUIRE(card.rank() == solitaire2::Rank::Ace);
    
    REQUIRE(card.is_red());
    REQUIRE(!card.is_black());
    REQUIRE(card.is_valid());

    CardType invalid_card(solitaire2::Suit::Hearts, solitaire2::Rank::Undef);
    REQUIRE(!invalid_card.is_valid());

    CardType card2(solitaire2::Suit::Spades, solitaire2::Rank::Six);
    REQUIRE(card2.is_black());
    REQUIRE(!card2.is_red());
    REQUIRE(card2.is_valid());

    REQUIRE(card.can_play_below(card2) == false);
    CardType card3(solitaire2::Suit::Diamonds, solitaire2::Rank::Five);
    REQUIRE(card3.can_play_below(card2) == true);   
    REQUIRE(card2.can_play_below(card3) == false);

}

TEST_CASE("Basic functionality of BasicCard") {
    test_card_functionality<solitaire2::BasicCard>();
}

TEST_CASE("Basic functionality of PackedCard") {
    test_card_functionality<solitaire2::PackedCard>();
}

template <typename CardType>
void test_deck_functionality(){
    solitaire2::Deck<CardType> deck;
    
    // check that all of the cards are valid
    std::array<uint8_t, 4> suit_counts = {0, 0, 0, 0};
    std::array<uint8_t, 14> rank_counts = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (uint8_t i = 0; i < 52; ++i) {
        auto card = deck.pick(i);
        REQUIRE(card.is_valid());
        suit_counts[static_cast<size_t>(card.suit())]++;
        rank_counts[static_cast<size_t>(card.rank())]++;
    }
    for (uint8_t i = 0; i < 4; ++i) {
        REQUIRE(suit_counts[i] == 13);
    }
    for (uint8_t i = 1; i <= 13; ++i) {
        REQUIRE(rank_counts[i] == 4);
    }
    // check that certain arbitrary cards are in the right place
    REQUIRE(deck.pick(0) == CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Ace));
    REQUIRE(deck.pick(12) == CardType(solitaire2::Suit::Hearts, solitaire2::Rank::King));
    REQUIRE(deck.pick(13) == CardType(solitaire2::Suit::Diamonds, solitaire2::Rank::Ace));
    REQUIRE(deck.pick(25) == CardType(solitaire2::Suit::Diamonds, solitaire2::Rank::King));
    REQUIRE(deck.pick(26) == CardType(solitaire2::Suit::Clubs, solitaire2::Rank::Ace));
    REQUIRE(deck.pick(38) == CardType(solitaire2::Suit::Clubs, solitaire2::Rank::King));
    REQUIRE(deck.pick(39) == CardType(solitaire2::Suit::Spades, solitaire2::Rank::Ace));
    REQUIRE(deck.pick(51) == CardType(solitaire2::Suit::Spades, solitaire2::Rank::King));

    deck.shuffle();
    // check that all of the cards are still valid after shuffling
    suit_counts = {0, 0, 0, 0};
    rank_counts = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (uint8_t i = 0; i < 52; ++i) {
        auto card = deck.pick(i);
        REQUIRE(card.is_valid());
        suit_counts[static_cast<size_t>(card.suit())]++;
        rank_counts[static_cast<size_t>(card.rank())]++;    
    }
    for (uint8_t i = 0; i < 4; ++i) {
        REQUIRE(suit_counts[i] == 13);
    }
    for (uint8_t i = 1; i <= 13; ++i) {
        REQUIRE(rank_counts[i] == 4);
    }
}

TEST_CASE("Basic functionality of Deck") {
    test_deck_functionality<solitaire2::BasicCard>();
    test_deck_functionality<solitaire2::PackedCard>();
}

TEST_CASE("Deck::pick throws out_of_range for invalid index") {
    solitaire2::Deck<solitaire2::BasicCard> deck;
    REQUIRE_THROWS_AS(deck.pick(52), std::out_of_range);
    REQUIRE_THROWS_AS(deck.pick(100), std::out_of_range);
    REQUIRE_THROWS_AS(deck.pick(255), std::out_of_range);
}

TEST_CASE("Card string representation and printing") {
    solitaire2::BasicCard card(solitaire2::Suit::Hearts, solitaire2::Rank::Ace);
    REQUIRE(solitaire2::to_string(card) == "A♥");
    REQUIRE(solitaire2::to_string(card.suit()) == "♥");
    REQUIRE(solitaire2::to_string(card.rank()) == "A");

    solitaire2::PackedCard packed_card(solitaire2::Suit::Spades, solitaire2::Rank::King);
    REQUIRE(solitaire2::to_string(packed_card) == "K♠");
    REQUIRE(solitaire2::to_string(packed_card.suit()) == "♠");
    REQUIRE(solitaire2::to_string(packed_card.rank()) == "K");

    printf("Printing BasicCard Ace of Hearts:\n");
    solitaire2::print_card(card);
    printf("\nPrinting PackedCard King of Spades:\n");
    solitaire2::print_card(packed_card);
    printf("\n");
}