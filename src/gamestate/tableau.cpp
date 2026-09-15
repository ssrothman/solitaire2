#include <solitaire2/gamestate/tableau.hpp>

using namespace solitaire2;

template <typename CardType>
BasicTableau<CardType>::BasicTableau(const std::vector<std::vector<CardType>>& face_down) : face_up_(), face_down_() {
    if (face_down.size() != 7) {
        throw std::invalid_argument("face_down vector must have size 7");
    }
    for (uint8_t i = 0; i < 7; ++i) {
        face_down_[i] = face_down[i];
    }
    // now flip up the top cards
    for (uint8_t i = 0; i < 7; ++i) {
        if (!face_down_[i].empty()) {
            face_up_[i].push_back(face_down_[i].back());
            face_down_[i].pop_back();
        }
    }
}

template <typename CardType>
uint8_t BasicTableau<CardType>::num_face_up(uint8_t index) const {
    return static_cast<uint8_t>(face_up_[index].size());
}

template <typename CardType>
uint8_t BasicTableau<CardType>::num_face_down(uint8_t index) const {
    return static_cast<uint8_t>(face_down_[index].size());
}

template <typename CardType>
const std::vector<CardType>& BasicTableau<CardType>::face_up(uint8_t index) const {
    return face_up_[index];
}

template <typename CardType>
void BasicTableau<CardType>::move_onto(std::vector<CardType> other, uint8_t index) { 
    face_up_[index].insert(face_up_[index].end(), other.begin(), other.end());
}

template <typename CardType>
std::vector<CardType> BasicTableau<CardType>::take_from(uint8_t num_take, uint8_t index) {
    if (num_take > face_up_[index].size()) {
        throw std::out_of_range("Not enough cards to take from tableau pile");
    }
    std::vector<CardType> taken(face_up_[index].end() - num_take, face_up_[index].end());
    face_up_[index].erase(face_up_[index].end() - num_take, face_up_[index].end());
    
    if (face_up_[index].empty() && !face_down_[index].empty()) {
        // flip the top face down card to face up
        face_up_[index].push_back(face_down_[index].back());
        face_down_[index].pop_back();
    }
    return taken;
}   

template class BasicTableau<BasicCard>;
template class BasicTableau<PackedCard>;
