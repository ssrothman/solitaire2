#ifndef SOLITAIRE2_MOVE_NOTATION_HPP
#define SOLITAIRE2_MOVE_NOTATION_HPP

#include <string>
#include <ostream>
#include <sstream>

#include <re2/re2.h>
#include <algorithm>

namespace solitaire2{

template <typename MoveType>
inline std::ostream& move_to_stream_(std::ostream& outs, const MoveType& move){
    switch(move.type()){
        case static_cast<uint8_t>(MoveKind::WasteToStock):
            outs << "StockReset";
            break;
        case static_cast<uint8_t>(MoveKind::StockToWaste):
            outs << "StockMill";
            break;
        case static_cast<uint8_t>(MoveKind::WasteToTableau):
            outs << "W→T" << static_cast<int>(move.target_index());
            break;
        case static_cast<uint8_t>(MoveKind::WasteToFoundation):
            outs << "W→F";
            break;
        case static_cast<uint8_t>(MoveKind::TableauToTableau):
            outs << "T" << static_cast<int>(move.source_index()) << "→T" << static_cast<int>(move.target_index());
            if (move.amount() != 1){
                outs << "(" << static_cast<int>(move.amount()) << ")";
            }
            break;
        case static_cast<uint8_t>(MoveKind::TableauToFoundation):
            outs << "T" << static_cast<int>(move.source_index()) << "→F";
            break;
    }
    return outs;
} //end move_to_stream_

/**
 * Move -> notation translation is really easy. 
 * Just use the lookup
 */
template <typename MoveType>
inline std::string move_to_notation(const MoveType& move){
        std::ostringstream ss;
        move_to_stream_(ss, move);
        return ss.str();
}

/**
 * Notation -> move is much trickier.
 * We want to be able to handle realistic user input
 * So there needs to be some amount of normalization and fuzziness
 */
inline bool is_whitespace(char test){
    return test == ' ' || test == '\n';
}

const re2::RE2 whitespace_regex("(\\s+)");
const re2::RE2 arrow_regex("(-+)>");
const re2::RE2 parse_regex("([A-Z]*)([0-9]*)?→([A-Z]*)([0-9])?\\(?([0-9]*)?\\)?");
const re2::RE2 counter_regex("([0-9]+)\\.(.*)");

inline int to_uppercase(int character){
    if (character >= 97 && character <= 122){
        return character - 32;
    } else {
        return character;
    }
}


/**
 * THIS MUTATES THE OUTPUT
 */
inline void normalize_notation_string(std::string& notation){
    // first, strip whitespace
    re2::RE2::GlobalReplace(&notation, whitespace_regex, "");

    // replace any `->` with `→`
    re2::RE2::GlobalReplace(&notation, arrow_regex, "→");

    std::transform(notation.begin(), notation.end(), notation.begin(), to_uppercase);
}

Location location_from_str(const std::string& loc){
    if (loc == "T"){
        return Location::Tableau;
    } else if (loc == "W"){
        return Location::Waste;   
    } else if (loc == "S"){
        return Location::Stock;
    } else if (loc == "F"){
        return Location::Foundation;
    } else {
        throw std::invalid_argument("Bad loc string");
    }
}

template <typename MoveType>
inline MoveType notation_to_move(std::string& notation){
    normalize_notation_string(notation);

    // A few special cases
    if (notation == "STOCKRESET" || notation == "RESET" || notation == "R"){
        return MoveType(Location::Waste, Location::Stock, 0, 0);
    } else if (notation == "STOCKMILL" || notation == "MILL" || notation == "DRAW" || notation == "D"){
        return MoveType(Location::Stock, Location::Waste, 0, 0);
    }

    // now we want to parse as SOURCE → TARGET
    std::string source_loc, source_idx, target_loc, target_idx, amount;
    bool success = re2::RE2::FullMatch(
        notation, parse_regex, 
        &source_loc, &source_idx,
        &target_loc, &target_idx,
        &amount
    );
    if (!success){
        throw std::invalid_argument("Bad notation string");
    }

    //printf(
    //    "Parsed as:\n\tSOURCE: (%s, %s)\n\tTARGET: (%s, %s)\n", 
    //    source_loc.c_str(), source_idx.c_str(),
    //    target_loc.c_str(), target_idx.c_str()
    //);

    Location source = location_from_str(source_loc);
    Location target = location_from_str(target_loc);

    uint8_t source_index = static_cast<uint8_t>(atoi(source_idx.c_str()));
    uint8_t target_index = static_cast<uint8_t>(atoi(target_idx.c_str()));

    printf("THE AMOUNT STRING IS: %s\n", amount.c_str());

    uint8_t amount_int = amount.empty() ? 1 : static_cast<uint8_t>(atoi(amount.c_str()));

    return MoveType(source, target, source_index, target_index, amount_int);
}

template <typename MoveType>
inline std::ostream& moves_to_stream(std::ostream& outs, const std::vector<MoveType>& moves){
    unsigned int counter = 0;
    for (const auto& move : moves){
        outs << counter << ". " << move_to_notation(move) << std::endl;
        counter++;
    }
    return outs;
}

template <typename MoveType>
inline std::vector<MoveType> stream_to_moves(std::istream& ins){
    std::vector<MoveType> moves;
    std::string line;

    std::string counter_str, move_str;

    while (std::getline(ins, line)){
        if (line.empty()){
            continue;
        }
        re2::RE2::FullMatch(line, counter_regex, &counter_str, &move_str);
        moves.push_back(notation_to_move<MoveType>(move_str));
    }
    return moves;
}

}; //end namespace solitaire2

#endif