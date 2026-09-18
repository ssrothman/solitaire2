"""Python package for the solitaire2 backend."""

from . import _core # pyright: ignore[reportMissingModuleSource]

__version__ = _core.__version__

BasicCard = _core.BasicCard
PackedCard = _core.PackedCard
Deck = _core.Deck
PackedCardDeck = _core.PackedCardDeck
BasicCardBasicGameDeck = _core.BasicCardBasicGameDeck
PackedCardBasicGameDeck = _core.PackedCardBasicGameDeck
BasicCardBasicTableau = _core.BasicCardBasicTableau
PackedCardBasicTableau = _core.PackedCardBasicTableau
BasicFoundation = _core.BasicFoundation
BasicGameBoard = _core.BasicGameBoard
PackedMove = _core.PackedMove
BasicMove = _core.BasicMove
Suit = _core.Suit
Rank = _core.Rank
Location = _core.Location
all_valid_moves = _core.all_valid_moves
all_valid_moves_packed = _core.all_valid_moves_packed

__all__ = [
	"__version__", "BasicCard", "PackedCard", "Deck", "PackedCardDeck",
	"BasicCardBasicGameDeck", "PackedCardBasicGameDeck",
	"BasicCardBasicTableau", "PackedCardBasicTableau", "BasicFoundation",
	"BasicGameBoard", "PackedMove", "BasicMove", "Suit", "Rank", "Location",
	"all_valid_moves", "all_valid_moves_packed",
]
