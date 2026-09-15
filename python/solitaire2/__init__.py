"""Python package for the solitaire2 backend."""

from . import _core

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

__all__ = [
	"__version__", "BasicCard", "PackedCard", "Deck", "PackedCardDeck",
	"BasicCardBasicGameDeck", "PackedCardBasicGameDeck",
	"BasicCardBasicTableau", "PackedCardBasicTableau", "BasicFoundation",
	"BasicGameBoard", "PackedMove", "BasicMove", "Suit", "Rank", "Location",
]
