#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/gamestate/gamedeck.hpp>
#include <solitaire2/prints.hpp>

using namespace solitaire2;

template <typename GameDeckType>
void test_gamedeck_functionality() {
    // test on a sorted deck, so we know what to expect
    Deck<typename GameDeckType::CardType> deck;
    
    GameDeckType gamedeck(deck.begin(), deck.end());

    // in initial state, waste should be empty, 
    // draw should be nonempty,
    // and the deck should have 52 cards
    REQUIRE(gamedeck.size() == 52);
    REQUIRE(gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    // when the waste is empty top_of_waste() should return an invalid card
    REQUIRE(gamedeck.top_of_waste().is_valid() == false);
    // when the waste is empty draw_from_waste() should throw an exception
    REQUIRE_THROWS_AS(gamedeck.draw_from_waste(), std::out_of_range);

    // now lets play with the deck a bit and see if everything works as expected

    // first, mill
    // stock should be nonempty
    // stock size should be 49
    // waste should be nonempty
    // top of waste should be the three of hearts
    gamedeck.mill();
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Three);
    REQUIRE(gamedeck.size() == 52);
    REQUIRE(gamedeck.stock_size() == 49);

    // draw from waste
    auto drawn_card = gamedeck.draw_from_waste();
    REQUIRE(drawn_card.suit() == Suit::Hearts);
    REQUIRE(drawn_card.rank() == Rank::Three);

    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Two);
    REQUIRE(gamedeck.size() == 51);
    REQUIRE(gamedeck.stock_size() == 49);

    // draw a second card from waste 
    drawn_card = gamedeck.draw_from_waste();
    REQUIRE(drawn_card.suit() == Suit::Hearts);
    REQUIRE(drawn_card.rank() == Rank::Two);

    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Ace);
    REQUIRE(gamedeck.size() == 50);
    REQUIRE(gamedeck.stock_size() == 49);

    // draw a third card from waste 
    drawn_card = gamedeck.draw_from_waste();
    REQUIRE(drawn_card.suit() == Suit::Hearts);
    REQUIRE(drawn_card.rank() == Rank::Ace);

    REQUIRE(gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Undef);
    REQUIRE(gamedeck.size() == 49);
    REQUIRE(gamedeck.stock_size() == 49);

    // trying to draw for a fourth time should error
    REQUIRE_THROWS_AS(gamedeck.draw_from_waste(), std::out_of_range);

    // now mill twice
    gamedeck.mill();
    gamedeck.mill();
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Nine);
    REQUIRE(gamedeck.size() == 49);
    REQUIRE(gamedeck.stock_size() == 43);

    // draw one card
    drawn_card = gamedeck.draw_from_waste();
    REQUIRE(drawn_card.suit() == Suit::Hearts);
    REQUIRE(drawn_card.rank() == Rank::Nine);

    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Eight);
    REQUIRE(gamedeck.size() == 48);
    REQUIRE(gamedeck.stock_size() == 43);

    // now mill to the end of the deck
    // should take ceil(43/3) = 15
    int num_mill = 0;
    while (!gamedeck.stock_empty()){
        gamedeck.mill();
        ++num_mill;
    }
    REQUIRE(num_mill == 15);
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.stock_empty());
    REQUIRE(gamedeck.size()==48);
    REQUIRE(gamedeck.stock_size() == 0);

    // now reset
    gamedeck.reset_draw();
    REQUIRE(gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Undef);
    REQUIRE(gamedeck.size() == 48);
    REQUIRE(gamedeck.stock_size() == 48);

    // if we mill twice we should now reveal the TEN of hearts
    gamedeck.mill();
    gamedeck.mill();
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.top_of_waste().suit() == Suit::Hearts);
    REQUIRE(gamedeck.top_of_waste().rank() == Rank::Ten);
    REQUIRE(gamedeck.size() == 48);
    REQUIRE(gamedeck.stock_size() == 42);


}

TEST_CASE("BasicGameDeck functionality"){
    test_gamedeck_functionality<BasicGameDeck<BasicCard>>();
    test_gamedeck_functionality<BasicGameDeck<PackedCard>>();
}