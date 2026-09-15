#ifndef SOLITAIRE2_MOVE_DISCOVERY_HPP
#define SOLITAIRE2_MOVE_DISCOVERY_HPP

#include <solitaire2/gamestate/board.hpp>
#include <solitaire2/moves.hpp>

namespace solitaire2 {

template <typename MoveType, typename BoardType>
inline void _tableau_to_foundation(std::vector<MoveType>& result, const BoardType& board){
    for (uint8_t pile=0; pile < 7; ++pile){
        const auto& thecards = board.tableau().face_up(pile);
        if (thecards.empty()){
            continue;
        }
        if (static_cast<uint8_t>(thecards[0].rank()) == static_cast<uint8_t>(board.foundation().at(thecards[0].suit())) + 1){
            result.emplace_back(
                Location::Tableau,
                Location::Foundation,
                pile,
                0
            );
        }
    }
}

template <typename MoveType, typename BoardType>
inline void _waste_to_foundation(std::vector<MoveType>& result, const BoardType& board){
    const auto& thecard = board.gamedeck().top_of_waste();
    if (static_cast<uint8_t>(thecard.rank()) == static_cast<uint8_t>(board.foundation().at(thecard.suit())) + 1){
        result.emplace_back(
            Location::Waste,
            Location::Foundation
        );
    }
}

template <typename MoveType, typename BoardType>
inline void _waste_to_tableau(std::vector<MoveType>& result, const BoardType& board){
    if (board.gamedeck().waste_empty()){
        return;
    }
    const auto& thecard = board.gamedeck().top_of_waste();
    for (uint8_t pile = 0; pile<7; ++pile){
        if (board.tableau().num_face_up(pile) > 0 && thecard.can_play_below(board.tableau().face_up(pile)[board.tableau().num_face_up(pile) - 1])){
            result.emplace_back(
                Location::Waste,
                Location::Tableau,
                0,
                pile
            );
        }
    }
}

template <typename MoveType, typename BoardType>
inline void _tableau_to_tableau(std::vector<MoveType>& result, const BoardType& board){
    for(uint8_t source_pile=0; source_pile < 7; ++source_pile){
        const auto& source_cards = board.tableau().face_up(source_pile);
        if (source_cards.empty()){
            continue;
        }
        for(uint8_t target_pile=0; target_pile < 7; ++target_pile){
            const auto& target_cards = board.tableau().face_up(target_pile);
            if (source_pile == target_pile){
                continue;
            }

            uint8_t amount = _tableau_to_tableau_helper(result, board, source_cards, target_cards);
            if (amount > 0){
                result.emplace_back(
                    Location::Tableau,
                    Location::Tableau,
                    source_pile,
                    target_pile,
                    amount
                );
            }
        }
    }
}

template <typename MoveType, typename BoardType, typename CardList>
inline uint8_t _tableau_to_tableau_helper(std::vector<MoveType>& result, const BoardType& board, 
                                       const CardList& source_cards, const CardList& target_cards){
    if (target_cards.empty()){
        if (source_cards[0].rank() == Rank::King){
            return source_cards.size();
        } else {
            return 0;
        }
    } else {
        const auto& target_card = target_cards[target_cards.size() - 1];

        for (uint8_t amount=1; amount <= source_cards.size(); ++amount){
            const auto& source_card = source_cards[source_cards.size() - amount];
            if (source_card.rank() >= target_card.rank()){
                return 0;
            }

            if (source_card.can_play_below(target_card)){
                return amount;
            }
        }
        return 0;
    }
}



template <typename MoveType, typename BoardType>
inline void _stock_manipulation(std::vector<MoveType>& result, const BoardType& board){
    if (board.gamedeck().waste_empty() && board.gamedeck().stock_empty()){
        return;
    } else if (board.gamedeck().stock_empty()){
        result.emplace_back(
            Location::Waste,
            Location::Stock
        );
    } else {
        result.emplace_back(
            Location::Stock,
            Location::Waste
        );
    }
}

template <typename MoveType, typename BoardType>
inline std::vector<MoveType> all_valid_moves(const BoardType& board){
    std::vector<MoveType> result;

    _tableau_to_foundation(result, board);
    _waste_to_foundation(result, board);
    _waste_to_tableau(result, board);
    _tableau_to_tableau(result, board);
    _stock_manipulation(result, board);

    return result;
}

}; // end namespace solitaire2

#endif