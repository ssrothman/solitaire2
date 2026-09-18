'''
Play the game on the command line
'''

from . import BasicGameBoard, all_valid_moves, BasicMove
from typing import Sequence, List
from .util import parseable_as_int

def _parse_command(line: str, board : BasicGameBoard, avail_moves : Sequence[BasicMove], history : List[BasicMove]):
    orig = line.strip()
    line = orig.upper()

    result = ''

    if line == 'HELP':
        result = "Commands:\n"
        result += '\thelp: display this help message.\n'
        result += '\tmoves: display the available moves\n'
        result += '\tboard: display the current board state (alias `state`)\n'
        result += 'treset [%d]: reset the board to play a new game with the provided seed'
        result += "\t[%d]: apply the i'th move from the list of avilable moves"

    elif line == 'MOVES':
        for i, move in enumerate(avail_moves):
            result += "%d. "%i + str(move) + '\n'

    elif line in ['BOARD', 'STATE']:
        result += str(board)

    elif line.startswith('RESET') and len(line.split(' ')) == 2 and parseable_as_int(line.split(' ')[1]):
        seed = int(line.split(' ')[1])
        board.reset(seed)
        result = "Starting game with seed [%d]\n"%seed
        result += "#############################\n"
        result += str(board)

    elif parseable_as_int(line):
        themove = avail_moves[int(line)]
        history.append(themove)
        board.apply_move(themove)
        
        avail_moves = all_valid_moves(board)
        result = str(board)

    else:
        result = "Invalid command `%s`. Type `help` to see available commands"%orig

    return result, avail_moves

def game_loop(seed = 0):
    print("Starting game with seed [%d]"%seed)
    print("#############################")

    board = BasicGameBoard(True, seed)
    avail_moves = all_valid_moves(board)
    history : List[BasicMove] = []
    print(board)

    while True:
        # read a line of input from stdin
        line = input(">> ")
        response, avail_moves = _parse_command(line, board, avail_moves, history)
        print(response)