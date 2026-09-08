#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/gamestate/gamedeck.hpp>
#include <solitaire2/prints.hpp>

template <typename GameDeckType>
void test_gamedeck_functionality() {
    // test on a sorted deck, so we know what to expect
    solitaire2::Deck<typename GameDeckType::CardType> deck;
    
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

    // draw a card from the draw pile
    // the drawn card should be the ace of hearts,
    // the waste should still be empty, 
    // and the draw should still be nonempty
    auto drawn_card = gamedeck.draw_from_stock();
    REQUIRE(drawn_card == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Ace));
    REQUIRE(gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());

    // draw another card from the waste pile
    // the drawn card should be the two of hearts,
    // the waste should still be empty,
    // and the draw should still be nonempty
    auto drawn_card2 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card2 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Two));
    REQUIRE(gamedeck.waste_empty());
    REQUIRE(!gamedeck.stock_empty());

    // now lets mill the deck
    // the waste will now be non-empty
    // the top card in the waste should be the five of hearts
    // and the draw should still be non-empty
    gamedeck.mill();
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Five));
    REQUIRE(!gamedeck.stock_empty());  

    // now lets draw again from the draw pile
    // the drawn card should be the six of hearts
    // the waste should still be non-empty
    // the top card in the waste should still be the five of hearts
    // and the draw should still be non-empty
    auto drawn_card3 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card3 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Six));
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Five));
    REQUIRE(!gamedeck.stock_empty());

    // now if we mill again 
    // the waste should still be non-empty
    // the top of the waste should now be the nine of hearts
    // and the draw should still be non-empty
    gamedeck.mill();
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Nine));
    REQUIRE(!gamedeck.stock_empty());    

    // now lets draw from the waste pile
    // the drawn card should be the nine of hearts
    // the waste should still be non-empty
    // the top of the waste should now be the eight of hearts
    // and the draw should still be non-empty
    auto drawn_card4 = gamedeck.draw_from_waste();
    REQUIRE(drawn_card4 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Nine));
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Eight));
    REQUIRE(!gamedeck.stock_empty());

    // if we draw from the waste pile again
    // the drawn card should be the eight of hearts
    // the waste should still be non-empty
    // the top of the waste should now be the seven of hearts
    // and the draw should still be non-empty
    auto drawn_card5 = gamedeck.draw_from_waste();
    REQUIRE(drawn_card5 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Eight));
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Seven));
    REQUIRE(!gamedeck.stock_empty());

    // if we draw from the waste again
    // we will now expose the top of the waste to be the five of hearts
    auto drawn_card6 = gamedeck.draw_from_waste();
    REQUIRE(drawn_card6 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Seven));
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Five));
    REQUIRE(!gamedeck.stock_empty());

    // and if we draw from the stock again
    // the drawn card should be the ten of hearts
    // the waste should still be non-empty
    // the top of the waste should still be the five of hearts
    // and the draw should still be non-empty
    auto drawn_card7 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card7 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Ten));
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Five));
    REQUIRE(!gamedeck.stock_empty());

    // now lets mill three times
    // the waste should still be non-empty
    // the top of the waste should now be the six of diamonds
    // and the draw should still be non-empty
    gamedeck.mill();
    gamedeck.mill();
    gamedeck.mill();
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Diamonds, solitaire2::Rank::Six));
    REQUIRE(!gamedeck.stock_empty());  

    // now lets mill until the stock is empty
    // it should take 11 mills to empty the stock
    uint8_t mill_count = 0;
    while (!gamedeck.stock_empty()) {
        gamedeck.mill();
        mill_count++;
    }
    REQUIRE(gamedeck.stock_empty());
    REQUIRE(mill_count == 11); 

    // now the stock should be empty
    // the waste should be non-empty
    // and the top of the waste should be the king of spades
    REQUIRE(gamedeck.stock_empty());
    REQUIRE(!gamedeck.waste_empty());
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Spades, solitaire2::Rank::King));  

    // drawing from the stock should now throw an exception
    REQUIRE_THROWS_AS(gamedeck.draw_from_stock(), std::out_of_range);

    // now we can reset the draw
    gamedeck.reset_draw();
    // the stock should now be non-empty
    // and the waste should be empty
    REQUIRE(!gamedeck.stock_empty());
    REQUIRE(gamedeck.waste_empty());
    // weve drawn seven cards, so there should be 45 left in the stock
    REQUIRE(gamedeck.size() == 45); 

    // now we can draw from the stock again
    // should be the three of hearts
    auto drawn_card8 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card8 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Three));
    
    // draw again: four of hearts
    auto drawn_card9 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card9 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Four));

    // draw again: five of hearts
    auto drawn_card10 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card10 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Five));

    // draw again: jack of hearts
    auto drawn_card11 = gamedeck.draw_from_stock();
    REQUIRE(drawn_card11 == typename GameDeckType::CardType(solitaire2::Suit::Hearts, solitaire2::Rank::Jack));

    // mill 
    gamedeck.mill();
    // the top of the waste should now be the Ace of diamonds
    REQUIRE(gamedeck.top_of_waste() == typename GameDeckType::CardType(solitaire2::Suit::Diamonds, solitaire2::Rank::Ace));
}

TEST_CASE("BasicGameDeck functionality"){
    test_gamedeck_functionality<solitaire2::BasicGameDeck<solitaire2::BasicCard>>();
    test_gamedeck_functionality<solitaire2::BasicGameDeck<solitaire2::PackedCard>>();
}