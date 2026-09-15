#include <catch2/catch_test_macros.hpp>

#include <solitaire2/cards.hpp>
#include <solitaire2/move_discovery.hpp>
#include <solitaire2/prints.hpp>
#include <solitaire2/gamestate/board.hpp>

using namespace solitaire2;

template <typename MoveType, typename BoardType>
void test_moves(std::vector<MoveType>& expected, std::vector<MoveType>& actual, const BoardType& board){
    REQUIRE(expected.size() == actual.size());

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

    for (size_t i=0; i<actual.size(); ++i){
        REQUIRE(expected[i] == actual[i]);
        REQUIRE(board.is_valid_move(expected[i]));
    }
}

TEST_CASE("Move discovery from sorted deck"){
    BasicGameBoard board(false);

    std::vector<BasicMove> expected_moves ({{
        BasicMove(
            Location::Tableau, 
            Location::Foundation,
            0,
            0
        ),
        BasicMove(
            Location::Tableau, 
            Location::Tableau,
            0, 
            6
        ),
        BasicMove(
            Location::Tableau,
            Location::Tableau,
            6, 1
        ),
        BasicMove(
            Location::Stock,
            Location::Waste
        )
    }});

    std::vector<BasicMove> moves = all_valid_moves<BasicMove, BasicGameBoard>(board);

    test_moves(moves, expected_moves, board);
}


TEST_CASE("Move discovery from initial state [seed 12]"){
    BasicGameBoard board(true, 12);

    std::vector<BasicMove> expected_moves ({{
        BasicMove(
            Location::Tableau, 
            Location::Tableau,
            3, 
            6
        ),
        BasicMove(
            Location::Stock,
            Location::Waste
        )
    }});

    std::vector<BasicMove> moves = all_valid_moves<BasicMove, BasicGameBoard>(board);
    test_moves(moves, expected_moves, board);
}

TEST_CASE("Move discovery from initial state [seed 9998]"){
    BasicGameBoard board(true, 9998);

    std::vector<BasicMove> expected_moves ({{
        BasicMove(
            Location::Tableau, 
            Location::Tableau,
            4, 
            3
        ),
        BasicMove(
            Location::Tableau, 
            Location::Tableau,
            6, 
            2
        ),
        BasicMove(
            Location::Stock,
            Location::Waste
        )
    }});

    std::vector<BasicMove> moves = all_valid_moves<BasicMove, BasicGameBoard>(board);
    
    test_moves(moves, expected_moves, board);
}
