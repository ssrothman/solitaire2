#include <solitaire2/gamestate/gamedeck.hpp>

#include <stdexcept>

template <typename CardType>
bool solitaire2::BasicGameDeck<CardType>::waste_empty() const noexcept {
    return draw_index_ == 0;
}
template <typename CardType>
bool solitaire2::BasicGameDeck<CardType>::stock_empty() const noexcept {
    return draw_index_ >= cards_.size();
}
template <typename CardType>
const CardType solitaire2::BasicGameDeck<CardType>::top_of_waste() const noexcept {
    if (draw_index_ > 0) {
        return cards_[draw_index_ - 1];
    } else {
        return invalid_card<CardType>();
    }
}

template <typename CardType>
CardType solitaire2::BasicGameDeck<CardType>::draw_from_waste() {
    if (waste_empty()) {
        throw std::out_of_range("Waste pile is empty in BasicGameDeck::draw_from_waste");
    } else {
        CardType card = cards_[draw_index_ - 1];
        cards_.erase(cards_.begin() + draw_index_ - 1);
        draw_index_--;
        return card;
    }
}

template <typename CardType>
void solitaire2::BasicGameDeck<CardType>::reset_draw() {
    draw_index_ = 0;
}

template <typename CardType>
void solitaire2::BasicGameDeck<CardType>::mill(){
    if (cards_.empty()) {
        throw std::out_of_range("Cannot mill an empty deck in BasicGameDeck::mill");
    }
    draw_index_ += 3;
}

template class solitaire2::BasicGameDeck<solitaire2::BasicCard>;
template class solitaire2::BasicGameDeck<solitaire2::PackedCard>;