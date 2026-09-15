#ifndef SOLITAIRE2_GAMESTATE_GAMEDECK_HPP
#define SOLITAIRE2_GAMESTATE_GAMEDECK_HPP

#include <solitaire2/cards.hpp>

namespace solitaire2 {
    /**
    * A basic game deck.
    * Naive implementation uses an std::vector<>
    */
   template <typename CardType_>
   class BasicGameDeck {
   public:
        typedef CardType_ CardType; 

        BasicGameDeck() : cards_(), draw_index_(0) {}

        template <typename T>
        BasicGameDeck(const T& begin, const T& end) : cards_(begin, end), draw_index_(0) {}
    
        // inspection methods
        bool waste_empty() const noexcept;
        bool stock_empty() const noexcept;
        const CardType top_of_waste() const noexcept;
        uint8_t size() const noexcept { return static_cast<uint8_t>(
            cards_.size()); 
        }
        uint8_t stock_size() const noexcept { 
            if (stock_empty()){
                return 0;
            } else {
                return static_cast<uint8_t>(cards_.size() - draw_index_); 
            }
        }

        // manipulation methods
        CardType draw_from_waste();
        void reset_draw();
        void mill();

   private:
       std::vector<CardType> cards_;
       uint8_t draw_index_;
}; // end class BasicGameDeck

}; // end namespace solitaire2

#endif