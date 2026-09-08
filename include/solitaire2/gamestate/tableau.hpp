#ifndef SOLITAIRE2_GAMESTATE_TABLEAU_HPP
#define SOLITAIRE2_GAMESTATE_TABLEAU_HPP

#include <solitaire2/cards.hpp>
#include <array>

/**
    Tableau piles
    Naive implementation as two vectors for face up/down cards
*/

namespace solitaire2{

template <typename CardType_>
class BasicTableau {
public:    
    using CardType = CardType_;
    using CardVector = std::vector<CardType>;

    BasicTableau() : face_up_(), face_down_() {}
    BasicTableau(const std::vector<CardVector>& face_down);

    // inspection
    uint8_t num_face_up(uint8_t index) const;
    uint8_t num_face_down(uint8_t index) const;
    const CardVector& face_up(uint8_t index) const;

    // manupulation
    void move_onto(CardVector other, uint8_t index);
    CardVector take_from(uint8_t num_take, uint8_t index);
    
private:
    std::array<CardVector, 7> face_up_;
    std::array<CardVector, 7> face_down_;

}; // end class BasicTableau

};//end namespace solitaire2

#endif