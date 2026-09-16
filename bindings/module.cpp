#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <solitaire2/cards.hpp>
#include <solitaire2/gamestate/board.hpp>
#include <solitaire2/gamestate/foundation.hpp>
#include <solitaire2/gamestate/gamedeck.hpp>
#include <solitaire2/gamestate/tableau.hpp>
#include <solitaire2/move_discovery.hpp>
#include <solitaire2/moves.hpp>
#include <solitaire2/prints.hpp>
#include <solitaire2/version.hpp>

namespace py = pybind11;

namespace {

template <typename Type>
std::string printed(const Type& value) {
    return solitaire2::to_string(value);
}

template <typename Type>
void add_printing(py::class_<Type>& binding) {
    binding.def("print", [](const Type& value) {
        py::print(printed(value), py::arg("end") = "");
    });
    binding.def("__str__", &printed<Type>);
    binding.def("__repr__", &printed<Type>);
}

template <typename CardType>
void bind_card(py::module_& module, const char* name) {
    auto binding = py::class_<CardType>(module, name);
    binding
        .def(py::init<solitaire2::Suit, solitaire2::Rank>())
        .def_property_readonly("suit", &CardType::suit)
        .def_property_readonly("rank", &CardType::rank)
        .def("is_red", &CardType::is_red)
        .def("is_black", &CardType::is_black)
        .def("is_valid", &CardType::is_valid)
        .def("can_play_below", &CardType::can_play_below)
        .def("__eq__", &CardType::operator==);
    add_printing(binding);
}

template <typename CardType>
void bind_deck(py::module_& module, const char* name) {
    using DeckType = solitaire2::Deck<CardType>;
    auto binding = py::class_<DeckType>(module, name);
    binding
        .def(py::init<>())
        .def("shuffle", &DeckType::shuffle)
        .def("pick", py::overload_cast<uint8_t>(&DeckType::pick), py::return_value_policy::reference_internal)
        .def("__len__", [](const DeckType&) { return 52; });
    add_printing(binding);
}

template <typename CardType>
void bind_game_deck(py::module_& module, const char* name) {
    using GameDeckType = solitaire2::BasicGameDeck<CardType>;
    auto binding = py::class_<GameDeckType>(module, name);
    binding
        .def(py::init<>())
        .def(py::init([](const std::vector<CardType>& cards) {
            return GameDeckType(cards.begin(), cards.end());
        }))
        .def("waste_empty", &GameDeckType::waste_empty)
        .def("stock_empty", &GameDeckType::stock_empty)
        .def("top_of_waste", &GameDeckType::top_of_waste)
        .def("size", &GameDeckType::size)
        .def("stock_size", &GameDeckType::stock_size)
        .def("draw_from_waste", &GameDeckType::draw_from_waste)
        .def("reset_draw", &GameDeckType::reset_draw)
        .def("mill", &GameDeckType::mill);
    add_printing(binding);
}

template <typename CardType>
void bind_tableau(py::module_& module, const char* name) {
    using TableauType = solitaire2::BasicTableau<CardType>;
    auto binding = py::class_<TableauType>(module, name);
    binding
        .def(py::init<>())
        .def(py::init<const std::vector<std::vector<CardType>>&>())
        .def("num_face_up", &TableauType::num_face_up)
        .def("num_face_down", &TableauType::num_face_down)
        .def("face_up", &TableauType::face_up)
        .def("move_onto", &TableauType::move_onto)
        .def("take_from", &TableauType::take_from);
    add_printing(binding);
}

template <typename MoveType>
void bind_move(py::module_& module, const char* name) {
    auto binding = py::class_<MoveType>(module, name);
    binding
        .def(py::init<>())
        .def(py::init<solitaire2::Location, solitaire2::Location, uint8_t, uint8_t, uint8_t>(),
             py::arg("source"), py::arg("target"), py::arg("source_index") = 0,
             py::arg("target_index") = 0, py::arg("amount") = 1)
        .def_property_readonly("source", &MoveType::source)
        .def_property_readonly("target", &MoveType::target)
        .def_property_readonly("source_index", &MoveType::source_index)
        .def_property_readonly("target_index", &MoveType::target_index)
        .def_property_readonly("type", &MoveType::type)
        .def_property_readonly("amount", &MoveType::amount)
        .def("__eq__", &MoveType::operator==);
    add_printing(binding);
}

} // namespace

PYBIND11_MODULE(_core, module) {
    module.doc() = "Python bindings for the solitaire2 backend scaffold.";
    module.attr("__version__") = solitaire2::version;

    py::enum_<solitaire2::Suit>(module, "Suit")
        .value("Hearts", solitaire2::Suit::Hearts)
        .value("Diamonds", solitaire2::Suit::Diamonds)
        .value("Clubs", solitaire2::Suit::Clubs)
        .value("Spades", solitaire2::Suit::Spades);
    py::enum_<solitaire2::Rank>(module, "Rank")
        .value("Undef", solitaire2::Rank::Undef)
        .value("Ace", solitaire2::Rank::Ace)
        .value("Two", solitaire2::Rank::Two)
        .value("Three", solitaire2::Rank::Three)
        .value("Four", solitaire2::Rank::Four)
        .value("Five", solitaire2::Rank::Five)
        .value("Six", solitaire2::Rank::Six)
        .value("Seven", solitaire2::Rank::Seven)
        .value("Eight", solitaire2::Rank::Eight)
        .value("Nine", solitaire2::Rank::Nine)
        .value("Ten", solitaire2::Rank::Ten)
        .value("Jack", solitaire2::Rank::Jack)
        .value("Queen", solitaire2::Rank::Queen)
        .value("King", solitaire2::Rank::King);
    py::enum_<solitaire2::Location>(module, "Location")
        .value("Waste", solitaire2::Location::Waste)
        .value("Stock", solitaire2::Location::Stock)
        .value("Tableau", solitaire2::Location::Tableau)
        .value("Foundation", solitaire2::Location::Foundation);

    bind_card<solitaire2::BasicCard>(module, "BasicCard");
    bind_card<solitaire2::PackedCard>(module, "PackedCard");
    bind_deck<solitaire2::BasicCard>(module, "Deck");
    bind_deck<solitaire2::PackedCard>(module, "PackedCardDeck");
    bind_game_deck<solitaire2::BasicCard>(module, "BasicCardBasicGameDeck");
    bind_game_deck<solitaire2::PackedCard>(module, "PackedCardBasicGameDeck");
    bind_tableau<solitaire2::BasicCard>(module, "BasicCardBasicTableau");
    bind_tableau<solitaire2::PackedCard>(module, "PackedCardBasicTableau");

    auto foundation = py::class_<solitaire2::BasicFoundation>(module, "BasicFoundation");
    foundation
        .def(py::init<>())
        .def("at", &solitaire2::BasicFoundation::at)
        .def("play_onto", &solitaire2::BasicFoundation::play_onto);
    add_printing(foundation);

    bind_move<solitaire2::PackedMove>(module, "PackedMove");
    bind_move<solitaire2::BasicMove>(module, "BasicMove");

    auto board = py::class_<solitaire2::BasicGameBoard>(module, "BasicGameBoard");
    board
        .def(py::init<bool, size_t>(), py::arg("shuffle") = true, py::arg("seed") = 0)
        .def("reset", &solitaire2::BasicGameBoard::reset)
        .def("gamedeck", &solitaire2::BasicGameBoard::gamedeck, py::return_value_policy::reference_internal)
        .def("foundation", &solitaire2::BasicGameBoard::foundation, py::return_value_policy::reference_internal)
        .def("tableau", &solitaire2::BasicGameBoard::tableau, py::return_value_policy::reference_internal)
        .def("is_valid_move", &solitaire2::BasicGameBoard::is_valid_move<solitaire2::BasicMove>)
        .def("apply_move", &solitaire2::BasicGameBoard::apply_move<solitaire2::BasicMove>);
    add_printing(board);

    module.def(
        "all_valid_moves",
        &solitaire2::all_valid_moves<solitaire2::BasicMove, solitaire2::BasicGameBoard>,
        py::arg("board"));
    module.def(
        "all_valid_moves_packed",
        &solitaire2::all_valid_moves<solitaire2::PackedMove, solitaire2::BasicGameBoard>,
        py::arg("board"));
}
