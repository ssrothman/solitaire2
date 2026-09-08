#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/gamestate/tableau.hpp>
#include <solitaire2/prints.hpp>

using namespace solitaire2;

template <typename TableauType>
void test_tableau() {
    TableauType tableau; // initialize empty tableau

    // all piles should have zero face up cards
    // zero face down cards
    // the face_up() query should return an empty vector
    // and take_from() should throw
    for (uint8_t i=0; i<7; ++i){
        REQUIRE(tableau.num_face_up(i) == 0);
        REQUIRE(tableau.num_face_down(i) == 0);
        REQUIRE(tableau.face_up(i).empty());
        REQUIRE_THROWS_AS(tableau.take_from(1, i), std::out_of_range);
    }

    // now initialize a tableau in the normal way
    Deck<typename TableauType::CardType> deck;
    std::vector<typename TableauType::CardVector> face_down(7);
    unsigned icard = 0;
    for (unsigned index = 0; index<7; ++index){
        for (unsigned j=0; j<=index; ++j){
            face_down[index].push_back(deck.pick(icard++));
        }
    }
    TableauType tableau2(face_down);

    // now all piles should have one face up card
    // and (index-1) face down cards
    // face_up() should return a vector of size 1
    // take_from(1) should return the expected vector of size 1
    // and take_from(2) should throw. 

    std::vector<typename TableauType::CardType> expected_face_up = {
        typename TableauType::CardType(Suit::Hearts, Rank::Ace),
        typename TableauType::CardType(Suit::Hearts, Rank::Three),
        typename TableauType::CardType(Suit::Hearts, Rank::Six),
        typename TableauType::CardType(Suit::Hearts, Rank::Ten),
        typename TableauType::CardType(Suit::Diamonds, Rank::Two),
        typename TableauType::CardType(Suit::Diamonds, Rank::Eight),
        typename TableauType::CardType(Suit::Clubs, Rank::Two)
    };

    for (uint8_t i=0; i<7; ++i){
        REQUIRE(tableau2.num_face_up(i) == 1);
        REQUIRE(tableau2.num_face_down(i) == i);

        REQUIRE_THROWS_AS(tableau2.take_from(2, i), std::out_of_range);

        auto face_up = tableau2.face_up(i);
        REQUIRE(face_up.size() == 1);
        auto taken = tableau2.take_from(1, i);
        REQUIRE(taken.size() == 1);
        REQUIRE(face_up[0] == taken[0]);
        REQUIRE(taken[0] == expected_face_up[i]);

        if (i==0){
            REQUIRE(tableau2.num_face_up(i) == 0);
            REQUIRE(tableau2.num_face_down(i) == 0);
            REQUIRE_THROWS_AS(tableau2.take_from(1, i), std::out_of_range);
        } else {
            REQUIRE(tableau2.num_face_up(i) == 1);
            REQUIRE(tableau2.num_face_down(i) == i-1);
        }
    }

    // now lets test moving cards between piles
    
    /**
     INITIAL STATE

     0:  
     1:  2-H
     2:  5-H
     3:  9-H
     4:  A-D
     5:  7-D
     6:  A-C
    */
    printf("-----INITIAL BOARD-----\n");
    print_tableau(tableau2);

    // move one card from pile 3 to pile 0
    tableau2.move_onto(
        tableau2.take_from(1, 3),
        0
    );
    REQUIRE(tableau2.num_face_up(0) == 1);
    REQUIRE(tableau2.num_face_down(0) == 0);
    REQUIRE(tableau2.num_face_up(3) == 1);
    REQUIRE(tableau2.num_face_down(3) == 1);

    /**
     CURRENT STATE [1]

     0:  9-H
     1:  2-H
     2:  5-H
     3:  8-H
     4:  A-D
     5:  7-D
     6:  A-C
    */
    printf("-----CURRENT STATE [1]-----\n");
    print_tableau(tableau2);


    // move another card from pile 3 to pile 0
    tableau2.move_onto(
        tableau2.take_from(1, 3),
        0
    );
    REQUIRE(tableau2.num_face_up(0) == 2);
    REQUIRE(tableau2.num_face_down(0) == 0);
    REQUIRE(tableau2.num_face_up(3) == 1);
    REQUIRE(tableau2.num_face_down(3) == 0);

    /**
    CURRENT STATE [2]

    0:  8-H  8-H
    1:  2-H
    2:  5-H
    3:  7-H
    4:  A-D
    5:  7-D
    6:  A-C
   */
   printf("-----CURRENT STATE [2]-----\n");
   print_tableau(tableau2);

    // move another card from pile 3 to pile 0
    tableau2.move_onto(
        tableau2.take_from(1, 3),
        0
    );
    REQUIRE(tableau2.num_face_up(0) == 3);
    REQUIRE(tableau2.num_face_down(0) == 0);
    REQUIRE(tableau2.num_face_up(3) == 0);
    REQUIRE(tableau2.num_face_down(3) == 0);

    /**
    CURRENT STATE [3]

    0:  9-H  8-H  7-H
    1:  2-H
    2:  5-H
    3:  
    4:  A-D
    5:  7-D
    6:  A-C
   */
   printf("-----CURRENT STATE [3]-----\n");
   print_tableau(tableau2);

    // attempting another move from pile 3 should throw
    REQUIRE_THROWS_AS(tableau2.take_from(1, 3), std::out_of_range);

    // now move two cards from pile 0 to pile 4
    tableau2.move_onto(
        tableau2.take_from(2, 0),
        4
    );
    REQUIRE(tableau2.num_face_up(0) == 1);
    REQUIRE(tableau2.num_face_down(0) == 0);
    REQUIRE(tableau2.num_face_up(4) == 3); 
    REQUIRE(tableau2.num_face_down(4) == 3);

    /**
    CURRENT STATE [4]

    0:  9-H  
    1:  2-H
    2:  5-H
    3:  
    4:  A-D  8-H  7-H
    5:  7-D
    6:  A-C
   */
   printf("-----CURRENT STATE [4]-----\n");
   print_tableau(tableau2);

    // now move one card from pile 4 to pile 5
    tableau2.move_onto(
        tableau2.take_from(1, 4),
        5
    );
    REQUIRE(tableau2.num_face_up(4) == 2);
    REQUIRE(tableau2.num_face_down(4) == 3);
    REQUIRE(tableau2.num_face_up(5) == 2);
    REQUIRE(tableau2.num_face_down(5) == 4);

    /**
    CURRENT STATE

    0:  9-H  
    1:  2-H
    2:  5-H
    3:  
    4:  A-D  8-H  
    5:  7-D  7-H
    6:  A-C
   */
   printf("-----CURRENT STATE-----\n");
   print_tableau(tableau2);

    // now move the last two cards from pile 4 to pile 2
    tableau2.move_onto(
        tableau2.take_from(2, 4),
        2
    );
    REQUIRE(tableau2.num_face_up(4) == 1);
    REQUIRE(tableau2.num_face_down(4) == 2);
    REQUIRE(tableau2.num_face_up(2) == 3);
    REQUIRE(tableau2.num_face_down(2) == 1);

    /**
    FINAL STATE

    0:  9-H  
    1:  2-H
    2:  5-H  A-D  8-H 
    3:  
    4:  K-H
    5:  7-D  7-H
    6:  A-C
   */

    printf("-----FINAL BOARD-----\n");
    print_tableau(tableau2);
    
   
    // now check all the face-up cards are as expected
    auto face_up0 = tableau2.face_up(0);
    REQUIRE(face_up0.size() == 1);
    REQUIRE(face_up0[0] == typename TableauType::CardType(Suit::Hearts, Rank::Nine));

    auto face_up1 = tableau2.face_up(1);
    REQUIRE(face_up1.size() == 1);
    REQUIRE(face_up1[0] == typename TableauType::CardType(Suit::Hearts, Rank::Two));

    auto face_up2 = tableau2.face_up(2);
    REQUIRE(face_up2.size() == 3);
    REQUIRE(face_up2[0] == typename TableauType::CardType(Suit::Hearts, Rank::Five));
    REQUIRE(face_up2[1] == typename TableauType::CardType(Suit::Diamonds, Rank::Ace));
    REQUIRE(face_up2[2] == typename TableauType::CardType(Suit::Hearts, Rank::Eight));

    auto face_up3 = tableau2.face_up(3);
    REQUIRE(face_up3.size() == 0);

    auto face_up4 = tableau2.face_up(4);
    REQUIRE(face_up4.size() == 1);
    REQUIRE(face_up4[0] == typename TableauType::CardType(Suit::Hearts, Rank::King));  

    auto face_up5 = tableau2.face_up(5);
    REQUIRE(face_up5.size() == 2);  
    REQUIRE(face_up5[0] == typename TableauType::CardType(Suit::Diamonds, Rank::Seven));
    REQUIRE(face_up5[1] == typename TableauType::CardType(Suit::Hearts, Rank::Seven));  

    auto face_up6 = tableau2.face_up(6);
    REQUIRE(face_up6.size() == 1);
    REQUIRE(face_up6[0] == typename TableauType::CardType(Suit::Clubs, Rank::Ace));

    // lastly move the last card from pile 0 to pile 6
    tableau2.move_onto(
        tableau2.take_from(1, 0),
        6
    );
    auto face_up0_final = tableau2.face_up(0);
    REQUIRE(face_up0_final.size() == 0);
    REQUIRE(tableau2.num_face_down(0) == 0);
    REQUIRE(tableau2.num_face_up(0) == 0);

    auto face_up6_final = tableau2.face_up(6);
    REQUIRE(face_up6_final.size() == 2);
    REQUIRE(face_up6_final[0] == typename TableauType::CardType(Suit::Clubs, Rank::Ace));
    REQUIRE(face_up6_final[1] == typename TableauType::CardType(Suit::Hearts, Rank::Nine));
    REQUIRE(tableau2.num_face_down(6) == 5);
    REQUIRE(tableau2.num_face_up(6) == 2);
}

TEST_CASE("BasicTableau functionality"){
    test_tableau<solitaire2::BasicTableau<solitaire2::BasicCard>>();
    test_tableau<solitaire2::BasicTableau<solitaire2::PackedCard>>();
}