#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/prints.hpp>
#include <solitaire2/gamestate/board.hpp>

using namespace solitaire2;

TEST_CASE("Basic board setup"){
    solitaire2::BasicGameBoard board(false);

    std::cout << board;

    REQUIRE(board.gamedeck().size() == 24);
    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 1);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0).at(0).rank() == Rank::Ace);
    REQUIRE(board.tableau().face_up(0).at(0).suit() == Suit::Hearts);

    REQUIRE(board.tableau().num_face_up(1) == 1);
    REQUIRE(board.tableau().num_face_down(1) == 1);
    REQUIRE(board.tableau().face_up(1).at(0).rank() == Rank::Three);
    REQUIRE(board.tableau().face_up(1).at(0).suit() == Suit::Hearts);

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 2);
    REQUIRE(board.tableau().face_up(2).at(0).rank() == Rank::Six);
    REQUIRE(board.tableau().face_up(2).at(0).suit() == Suit::Hearts);

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3).at(0).rank() == Rank::Ten);
    REQUIRE(board.tableau().face_up(3).at(0).suit() == Suit::Hearts);

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4).at(0).rank() == Rank::Two);
    REQUIRE(board.tableau().face_up(4).at(0).suit() == Suit::Diamonds);

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5).at(0).rank() == Rank::Eight);
    REQUIRE(board.tableau().face_up(5).at(0).suit() == Suit::Diamonds);

    REQUIRE(board.tableau().num_face_up(6) == 1);
    REQUIRE(board.tableau().num_face_down(6) == 6);
    REQUIRE(board.tableau().face_up(6).at(0).rank() == Rank::Two);
    REQUIRE(board.tableau().face_up(6).at(0).suit() == Suit::Clubs);
}

TEST_CASE("Apply moves"){
    solitaire2::BasicGameBoard board(false);

    /* 
    STATE:
        -- -- -- --

        0: [0] A♥
        1: [1] 3♥
        2: [2] 6♥
        3: [3] 10♥
        4: [4] 2♦
        5: [5] 8♦
        6: [6] 2♣


        [24]
    */

    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 1);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0)[0] == BasicCard(Suit::Hearts, Rank::Ace));

    REQUIRE(board.tableau().num_face_up(1) == 1);
    REQUIRE(board.tableau().num_face_down(1) == 1);
    REQUIRE(board.tableau().face_up(1)[0] == BasicCard(Suit::Hearts, Rank::Three));

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 2);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Six));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 1);
    REQUIRE(board.tableau().num_face_down(6) == 6);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Clubs, Rank::Two));

    REQUIRE(board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 24);




    // now apply T0 -> F
    board.apply_move(BasicMove(Location::Tableau, Location::Foundation, 0, 0));

    /* 
    STATE:
        A♥ -- -- --

        0: [0] 
        1: [1] 3♥
        2: [2] 6♥
        3: [3] 10♥
        4: [4] 2♦
        5: [5] 8♦
        6: [6] 2♣


        [24]
    */


    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Ace);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 0);
    REQUIRE(board.tableau().num_face_down(0) == 0);

    REQUIRE(board.tableau().num_face_up(1) == 1);
    REQUIRE(board.tableau().num_face_down(1) == 1);
    REQUIRE(board.tableau().face_up(1)[0] == BasicCard(Suit::Hearts, Rank::Three));

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 2);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Six));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 1);
    REQUIRE(board.tableau().num_face_down(6) == 6);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Clubs, Rank::Two));

    REQUIRE(board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 24);

    // now try T6 -> T0 and T2 -> T0
    board.apply_move(BasicMove(Location::Tableau, Location::Tableau, 6, 0));
    board.apply_move(BasicMove(Location::Tableau, Location::Tableau, 2, 0));

    /* 
    STATE:
        A♥ -- -- --

        0: [0] 2♣ 6♥
        1: [1] 3♥
        2: [1] 5♥
        3: [3] 10♥
        4: [4] 2♦
        5: [5] 8♦
        6: [5] A♣


        [24]
    */

    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Ace);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 2);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0)[0] == BasicCard(Suit::Clubs, Rank::Two));
    REQUIRE(board.tableau().face_up(0)[1] == BasicCard(Suit::Hearts, Rank::Six));

    REQUIRE(board.tableau().num_face_up(1) == 1);
    REQUIRE(board.tableau().num_face_down(1) == 1);
    REQUIRE(board.tableau().face_up(1)[0] == BasicCard(Suit::Hearts, Rank::Three));

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 1);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Five));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 1);
    REQUIRE(board.tableau().num_face_down(6) == 5);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Clubs, Rank::Ace));

    REQUIRE(board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 24);

    // try T1 -> F and T6 -> F and T0 -> F and T1 -> F
    board.apply_move(BasicMove(Location::Tableau, Location::Foundation, 1, 0));
    board.apply_move(BasicMove(Location::Tableau, Location::Foundation, 6, 0));
    board.apply_move(BasicMove(Location::Tableau, Location::Foundation, 0, 0));
    board.apply_move(BasicMove(Location::Tableau, Location::Foundation, 1, 0));


    /* 
    STATE:
        4♥ -- A♣ --

        0: [0] 2♣ 
        1: [0] 
        2: [1] 5♥
        3: [3] 10♥
        4: [4] 2♦
        5: [5] 8♦
        6: [4] K♦

        [24]
    */

    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Four);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Ace);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 1);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0)[0] == BasicCard(Suit::Clubs, Rank::Two));

    REQUIRE(board.tableau().num_face_up(1) == 0);
    REQUIRE(board.tableau().num_face_down(1) == 0);

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 1);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Five));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 1);
    REQUIRE(board.tableau().num_face_down(6) == 4);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Diamonds, Rank::King));

    REQUIRE(board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 24);

    // stock milling
    board.apply_move(BasicMove(Location::Stock, Location::Waste, 0, 0));
    board.apply_move(BasicMove(Location::Stock, Location::Waste, 0, 0));
    board.apply_move(BasicMove(Location::Stock, Location::Waste, 0, 0));

    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Four);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Ace);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 1);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0)[0] == BasicCard(Suit::Clubs, Rank::Two));

    REQUIRE(board.tableau().num_face_up(1) == 0);
    REQUIRE(board.tableau().num_face_down(1) == 0);

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 1);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Five));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 1);
    REQUIRE(board.tableau().num_face_down(6) == 4);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Diamonds, Rank::King));

    REQUIRE(!board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 15);
    REQUIRE(board.gamedeck().top_of_waste() == BasicCard(Suit::Clubs, Rank::Jack));

    // waste to tableau and foundation
    board.apply_move(BasicMove(Location::Waste, Location::Foundation, 0, 0));
    board.apply_move(BasicMove(Location::Waste, Location::Tableau, 0, 6));

    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Four);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Two);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 1);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0)[0] == BasicCard(Suit::Clubs, Rank::Two));

    REQUIRE(board.tableau().num_face_up(1) == 0);
    REQUIRE(board.tableau().num_face_down(1) == 0);

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 1);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Five));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 2);
    REQUIRE(board.tableau().num_face_down(6) == 4);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Diamonds, Rank::King));
    REQUIRE(board.tableau().face_up(6)[1] == BasicCard(Suit::Clubs, Rank::Ten));

    REQUIRE(!board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 15);
    REQUIRE(board.gamedeck().top_of_waste() == BasicCard(Suit::Clubs, Rank::Nine));

    // stock reset
    board.apply_move(BasicMove(Location::Waste, Location::Stock, 0, 0));

    REQUIRE(board.foundation().at(Suit::Hearts) == Rank::Four);
    REQUIRE(board.foundation().at(Suit::Diamonds) == Rank::Undef);
    REQUIRE(board.foundation().at(Suit::Clubs) == Rank::Two);
    REQUIRE(board.foundation().at(Suit::Spades) == Rank::Undef);

    REQUIRE(board.tableau().num_face_up(0) == 1);
    REQUIRE(board.tableau().num_face_down(0) == 0);
    REQUIRE(board.tableau().face_up(0)[0] == BasicCard(Suit::Clubs, Rank::Two));

    REQUIRE(board.tableau().num_face_up(1) == 0);
    REQUIRE(board.tableau().num_face_down(1) == 0);

    REQUIRE(board.tableau().num_face_up(2) == 1);
    REQUIRE(board.tableau().num_face_down(2) == 1);
    REQUIRE(board.tableau().face_up(2)[0] == BasicCard(Suit::Hearts, Rank::Five));

    REQUIRE(board.tableau().num_face_up(3) == 1);
    REQUIRE(board.tableau().num_face_down(3) == 3);
    REQUIRE(board.tableau().face_up(3)[0] == BasicCard(Suit::Hearts, Rank::Ten));

    REQUIRE(board.tableau().num_face_up(4) == 1);
    REQUIRE(board.tableau().num_face_down(4) == 4);
    REQUIRE(board.tableau().face_up(4)[0] == BasicCard(Suit::Diamonds, Rank::Two));

    REQUIRE(board.tableau().num_face_up(5) == 1);
    REQUIRE(board.tableau().num_face_down(5) == 5);
    REQUIRE(board.tableau().face_up(5)[0] == BasicCard(Suit::Diamonds, Rank::Eight));

    REQUIRE(board.tableau().num_face_up(6) == 2);
    REQUIRE(board.tableau().num_face_down(6) == 4);
    REQUIRE(board.tableau().face_up(6)[0] == BasicCard(Suit::Diamonds, Rank::King));
    REQUIRE(board.tableau().face_up(6)[1] == BasicCard(Suit::Clubs, Rank::Ten));

    REQUIRE(board.gamedeck().waste_empty());
    REQUIRE(board.gamedeck().stock_size() == 22);


}