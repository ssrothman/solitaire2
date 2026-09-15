#ifndef SOLITAIRE2_MOVES_HPP
#define SOLITAIRE2_MOVES_HPP

#include <cstdint>

namespace solitaire2 {

enum class Location : uint8_t {
    Waste = 0,
    Stock = 1,
    Tableau = 2,
    Foundation = 3
};

/**
 * For utility -- just an enumeration of the possible Location, Location pairs
 * 
 * We only include those values that correspond to valid moves
 */
enum class MoveKind : uint8_t {
    WasteToStock = 0b0001,
    StockToWaste = 0b0100, 

    WasteToTableau = 0b0010,
    WasteToFoundation = 0b0011, 
    
    TableauToTableau = 0b1010,
    TableauToFoundation = 0b1011
};
    
class PackedMove {
public:
    PackedMove() :
        type_(0), index_(0) {}
        
    PackedMove(Location source, Location target, uint8_t source_index, uint8_t target_index) : 
        type_( (static_cast<uint8_t>(source) << 2) | static_cast<uint8_t>(target)),
        index_ ((source_index << 4) | target_index) {}

    Location source() const {
        return static_cast<Location>((type_ >> 2) & 0b11);
    }
    Location target() const {
        return static_cast<Location>(type_ & 0b11);
    }

    uint8_t source_index() const {
        return (index_ >> 4) & 0b1111;
    }
    uint8_t target_index() const {
        return index_ & 0b1111;
    }

    uint8_t type() const {
        return type_;
    }
private:
    /**
     * Packed Locations for the source and destination
     * Eight bits, organized as:
     * [unused][unused][unused][unused][source][source][target][target]
     */
    uint8_t type_;
    /**
     * Packed indices for the source and destination
     * Eight bits, organized as
     * [source][source][source][source][target][target][target][target]
     */
    uint8_t index_;
};

class BasicMove {
public:
    BasicMove() :
        source_(Location::Waste),
        target_(Location::Waste),
        source_index_(0),
        target_index_(0),
        type_(0) {}

    BasicMove(Location source, Location target, uint8_t source_index, uint8_t target_index):
        source_(source), target_(target),
        source_index_(source_index),
        target_index_(target_index),
        type_((static_cast<uint8_t>(source) << 2) | static_cast<uint8_t>(target)) {}

    Location source() const {
        return source_;
    }
    Location target() const {
        return target_;
    }

    uint8_t source_index() const {
        return source_index_;
    }
    uint8_t target_index() const {
        return target_index_;
    }

    uint8_t type() const {
        return type_;
    }
private:
    Location source_;
    Location target_;
    uint8_t type_;
    uint8_t source_index_;
    uint8_t target_index_;
};

}; // end namespace solitaire2

#endif