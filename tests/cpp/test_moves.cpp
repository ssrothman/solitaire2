#include <catch2/catch_test_macros.hpp>

#include <solitaire2/moves.hpp>
#include <solitaire2/prints.hpp>

using namespace solitaire2;

template <typename MoveType> 
void test_moves(){
    MoveType move1(Location::Waste, Location::Tableau, 2, 4);
    REQUIRE(move1.source() == Location::Waste);
    REQUIRE(move1.target() == Location::Tableau);
    REQUIRE(move1.type() == static_cast<uint8_t>(MoveKind::WasteToTableau));
    REQUIRE(move1.source_index() == 2);
    REQUIRE(move1.target_index() == 4);

    MoveType move2(Location::Waste, Location::Foundation, 0, 0);
    REQUIRE(move2.source() == Location::Waste);
    REQUIRE(move2.target() == Location::Foundation);
    REQUIRE(move2.type() == static_cast<uint8_t>(MoveKind::WasteToFoundation));
    REQUIRE(move2.source_index() == 0);
    REQUIRE(move2.target_index() == 0);

    MoveType move3(Location::Tableau, Location::Tableau, 5, 2);
    REQUIRE(move3.source() == Location::Tableau);
    REQUIRE(move3.target() == Location::Tableau);
    REQUIRE(move3.type() == static_cast<uint8_t>(MoveKind::TableauToTableau));
    REQUIRE(move3.source_index() == 5);
    REQUIRE(move3.target_index() == 2);

    MoveType move4(Location::Tableau, Location::Foundation, 3, 0);
    REQUIRE(move4.source() == Location::Tableau);
    REQUIRE(move4.target() == Location::Foundation);
    REQUIRE(move4.type() == static_cast<uint8_t>(MoveKind::TableauToFoundation));
    REQUIRE(move4.source_index() == 3);
    REQUIRE(move4.target_index() == 0);

    MoveType move5(Location::Waste, Location::Stock, 0, 0);
    REQUIRE(move5.source() == Location::Waste);
    REQUIRE(move5.target() == Location::Stock);
    REQUIRE(move5.type() == static_cast<uint8_t>(MoveKind::WasteToStock));

    MoveType move6(Location::Stock, Location::Waste, 0, 0);
    REQUIRE(move6.source() == Location::Stock);
    REQUIRE(move6.target() == Location::Waste);
    REQUIRE(move6.type() == static_cast<uint8_t>(MoveKind::StockToWaste));
}

TEST_CASE("Moves are not ill-formed"){
    test_moves<BasicMove>();
    test_moves<PackedMove>();
}