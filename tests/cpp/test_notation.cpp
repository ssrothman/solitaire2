#include <catch2/catch_test_macros.hpp>

#include <solitaire2/moves.hpp>
#include <solitaire2/move_notation.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace solitaire2;

TEST_CASE("Notation normalization"){
    REQUIRE(whitespace_regex.ok());

    std::string test_input("a B -> --> -----> c\t\td\n\naSdfy\n");
    normalize_notation_string(test_input);
    REQUIRE(test_input == "AB→→→CDASDFY");

}

TEST_CASE("Notation parsing throws on bad inputs"){
    std::string test_input = "A1 -> B";
    REQUIRE_THROWS_AS(notation_to_move<BasicMove>(test_input), std::invalid_argument);

    test_input = "A1 ->-> B";
    REQUIRE_THROWS_AS(notation_to_move<BasicMove>(test_input), std::invalid_argument);

    test_input = "T1 -> _F";
    REQUIRE_THROWS_AS(notation_to_move<BasicMove>(test_input), std::invalid_argument);

    test_input = "T1?! -> F";
    REQUIRE_THROWS_AS(notation_to_move<BasicMove>(test_input), std::invalid_argument);
}

TEST_CASE("Notation parsing works on good inputs"){
    std::string test_input = "W -> S";
    BasicMove testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Waste);
    REQUIRE(testmove.target() == Location::Stock);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::WasteToStock));

    test_input = "S -> W";
    testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Stock);
    REQUIRE(testmove.target() == Location::Waste);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::StockToWaste));

    test_input = "W -> T1";
    testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Waste);
    REQUIRE(testmove.target() == Location::Tableau);
    REQUIRE(testmove.target_index() == 1);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::WasteToTableau));

    test_input = "W -> T4";
    testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Waste);
    REQUIRE(testmove.target() == Location::Tableau);
    REQUIRE(testmove.target_index() == 4);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::WasteToTableau));

    test_input = "W -> F";
    testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Waste);
    REQUIRE(testmove.target() == Location::Foundation);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::WasteToFoundation));

    test_input = "T2 -> T6";
    testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Tableau);
    REQUIRE(testmove.target() == Location::Tableau);
    REQUIRE(testmove.target_index() == 6);
    REQUIRE(testmove.source_index() == 2);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::TableauToTableau));

    test_input = "T0 -> F";
    testmove = notation_to_move<BasicMove>(test_input);
    REQUIRE(testmove.source() == Location::Tableau);
    REQUIRE(testmove.target() == Location::Foundation);
    REQUIRE(testmove.source_index() == 0);
    REQUIRE(testmove.type() == static_cast<uint8_t>(MoveKind::TableauToFoundation));
}

TEST_CASE("Notation parsing round trip"){
    BasicMove testmove(Location::Waste, Location::Stock, 0, 0);
    std::string notation = move_to_notation(testmove);
    BasicMove roundtrip = notation_to_move<BasicMove>(notation);
    REQUIRE(roundtrip == testmove);

    testmove = BasicMove(Location::Stock, Location::Waste, 0, 0);
    notation = move_to_notation(testmove);
    roundtrip = notation_to_move<BasicMove>(notation);
    REQUIRE(roundtrip == testmove);

    testmove = BasicMove(Location::Waste, Location::Tableau, 0, 3);
    notation = move_to_notation(testmove);
    roundtrip = notation_to_move<BasicMove>(notation);
    REQUIRE(roundtrip == testmove);

    testmove = BasicMove(Location::Waste, Location::Foundation, 0, 0);
    notation = move_to_notation(testmove);
    roundtrip = notation_to_move<BasicMove>(notation);
    REQUIRE(roundtrip == testmove);

    testmove = BasicMove(Location::Tableau, Location::Foundation, 2, 0);
    notation = move_to_notation(testmove);
    roundtrip = notation_to_move<BasicMove>(notation);
    REQUIRE(roundtrip == testmove);

    testmove = BasicMove(Location::Tableau, Location::Tableau, 1, 5);
    notation = move_to_notation(testmove);
    roundtrip = notation_to_move<BasicMove>(notation);
    REQUIRE(roundtrip == testmove);
}

TEST_CASE("Bulk notation writing and parsing"){
    std::vector<BasicMove> moves = {
        BasicMove(Location::Waste, Location::Stock, 0, 0),
        BasicMove(Location::Stock, Location::Waste, 0, 0),
        BasicMove(Location::Waste, Location::Tableau, 0, 3),
        BasicMove(Location::Waste, Location::Foundation, 0, 0),
        BasicMove(Location::Tableau, Location::Foundation, 2, 0),
        BasicMove(Location::Tableau, Location::Tableau, 1, 5)
    };

    std::ofstream outs("test_moves.txt", std::ios::out | std::ios::trunc);
    moves_to_stream<BasicMove>(outs, moves);
    outs.close();

    std::ifstream ins("test_moves.txt", std::ios::in);
    std::vector<BasicMove> roundtrip = stream_to_moves<BasicMove>(ins);
    ins.close();

    REQUIRE(roundtrip.size() == moves.size());
    for (size_t i = 0; i < moves.size(); ++i){
        REQUIRE(roundtrip[i] == moves[i]);
    }

    std::remove("test_moves.txt");
}