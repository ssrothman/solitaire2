#ifndef SOLITAIRE2_CARDS_HPP
#define SOLITAIRE2_CARDS_HPP

#include <random>
#include <stdexcept>
#include <algorithm>

namespace solitaire2 {
/*
 * Card suit.
 * Suits are organized such that the second bit indicates whether the suit is red (Hearts, Diamonds = 0,1),
 *       or black (Clubs, Spades = 2,3).
 */
enum class Suit : uint8_t {
    Hearts = 0,
    Diamonds = 1,
    Clubs = 2,
    Spades = 3
}; // end enum class Suit
/*
 * Card rank.
 * Aces are always low
 * Rank=0 is invalid; valid ranks are 1-13 (Ace-King)
 */
enum class Rank : uint8_t {
    Undef = 0,
    Ace = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 11,
    Queen = 12,
    King = 13
}; //end enum class Rank

// operator++ for Ranks
inline Rank& operator++(Rank& rank){
    if (static_cast<uint8_t>(rank) >= 13){
        throw std::out_of_range("Cannot increment rank::King");
    } else {
        return rank = static_cast<Rank>(static_cast<uint8_t>(rank) + 1);
    }
}

/*
 * A basic card representation.
 * This is a simple struct that holds a suit and rank, and provides some utility functions.
 * It is not optimized for space or performance, but is easy to use and understand.
*/
class BasicCard {
public:
    BasicCard() : suit_(Suit::Hearts), rank_(Rank::Undef) {}
    BasicCard(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}

    Suit suit() const { return suit_; }
    Rank rank() const { return rank_; }

    bool is_red() const noexcept { 
        return (static_cast<uint8_t>(suit_) & 0b10) == 0; 
    }
    bool is_black() const noexcept { 
        return (static_cast<uint8_t>(suit_) & 0b10) != 0; 
    }

    bool is_valid() const noexcept {
        return static_cast<uint8_t>(suit_) <= static_cast<uint8_t>(Suit::Spades) &&
               static_cast<uint8_t>(rank_) <= static_cast<uint8_t>(Rank::King) &&
               rank_ != Rank::Undef;
    }

    bool operator==(const BasicCard& other) const noexcept {
        return suit_ == other.suit_ && rank_ == other.rank_;
    }

    bool can_play_below(const BasicCard& other) const noexcept {
        return is_red() != other.is_red() && static_cast<uint8_t>(rank_) + 1 == static_cast<uint8_t>(other.rank_);
    }
private:
    Suit suit_;
    Rank rank_;
}; // end class BasicCard


/*
 * Packed card representation --- fits entire card into a single uint8_t. 
 * PackedCard is organized such that the two least significant bits represent the suit (0-3),
 *                                   the next four bits represent the rank (1-13),
 *                                   and the two most significant bits are unused (undefined).4
 * i.e., the structure looks like [unused][unused][rank4][rank3][rank2][rank1][suit1][suit0]
 *
 * Maybe we can think of a clever use for those top two bits later.
*/
class PackedCard {
public:
    PackedCard() : data_(0) {}
    PackedCard(Suit suit, Rank rank) : data_((static_cast<uint8_t>(rank) << 2) | static_cast<uint8_t>(suit)) {}

    Suit suit() const noexcept { 
        return static_cast<Suit>(data_ & 0b11); 
    }
    Rank rank() const noexcept { 
        return static_cast<Rank>((data_ >> 2) & 0b1111); 
    }

    bool is_red() const noexcept { 
        return (data_ & 0b10) == 0; 
    }
    bool is_black() const noexcept {
         return (data_ & 0b10) != 0; 
        }

    bool is_valid() const noexcept{
        return static_cast<uint8_t>(suit()) <= static_cast<uint8_t>(Suit::Spades) &&
               static_cast<uint8_t>(rank()) <= static_cast<uint8_t>(Rank::King) &&
               rank() != Rank::Undef;
    }

    bool operator==(const PackedCard& other) const noexcept {
        return data_ == other.data_;
    }

    bool can_play_below(const PackedCard& other) const noexcept {
        return ((data_ & 0b10) != (other.data_ & 0b10)) && (((data_ >> 2) & 0b1111) + 1 == ((other.data_ >> 2) & 0b1111));
    }
    
private:
    uint8_t data_;
}; //end class PackedCard

template <typename CardType>
constexpr CardType invalid_card() {
    return CardType(Suit::Hearts, Rank::Undef);
}

template <class CardType>
class Deck {
public:
    Deck(){
        initialize_deck();
    };

    void shuffle(size_t seed) noexcept {
        std::mt19937 g(seed);
        std::shuffle(cards_.begin(), cards_.end(), g);
    }

    CardType& pick(uint8_t index) {
        if (index < cards_.size()) {
            return cards_[index];
        } else {
            throw std::out_of_range("Index out of range in Deck::pick");
        }
    }

    const CardType& pick(uint8_t index) const {
        if (index < cards_.size()) {
            return cards_[index];
        } else {
            throw std::out_of_range("Index out of range in Deck::pick");
        }
    }

    auto begin() { return cards_.begin(); }
    auto end() { return cards_.end(); }

private:
    std::array<CardType, 52> cards_;

    void initialize_deck() noexcept {
        uint8_t index = 0;
        for (uint8_t suit = 0; suit < 4; ++suit) {
            for (uint8_t rank = 1; rank <= 13; ++rank) {
                cards_[index++] = CardType(static_cast<Suit>(suit), static_cast<Rank>(rank));
            }
        }
    }
}; // end class Deck

}; // end namespace solitaire2

#endif