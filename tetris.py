

board = [['.' for _ in range(10)] for _ in range(10)]

pieces = [
    [[2, 7, 6, 11], [6, 7, 12, 13]],
    [[1, 2, 7, 12], [6, 7, 8, 3], [13, 12, 7, 2], [11, 6, 7, 8]],
    [[2, 7, 12, 17, 22], [10, 11, 12, 13, 14, 15]]
]


def is_piece_valid(board, piece, x, y):
    for field in piece:
        xx = field % 5 + x
        yy = field // 5 + y
        if board[yy][xx] != '.':
            return False
    return True


def put_piece(board_orig, piece, x, y, char, ok):
    board = [row[::] for row in board_orig]
    for field in piece:
        xx = field % 5 + x
        yy = field // 5 + y
        if board[yy][xx] != '.' and char != '.':
            raise Exception('invalid!')
        if ok: board[yy][xx] = char
    for i in range(10):
        board_orig[i] = board[i]
    

def print_board(board):
    for row in board:
        print(' '.join(row))

from collections import defaultdict
dx = defaultdict(int)
dx['L'] = -1
dx['R'] = 1
dy = defaultdict(int)
dy['D'] = 1
dr = defaultdict(int)
dr['Q'] = -1
dr['E'] = 1

moves = 'DDDLREQDEED'

from random import choice

piece_masks = choice(pieces)
rotation = 0
x = 4
y = 0
put_piece(board, piece_masks[rotation], 4, 0, 'X', True)
print_board(board)
input()
for move in moves:
    try:
        put_piece(board, piece_masks[rotation], x, y, '.', True)
        x += dx[move]
        y += dy[move]
        rotation = (rotation + dr[move]) % len(piece_masks)
        put_piece(board, piece_masks[rotation], x, y, 'X', True)
        print_board(board)
    except:
        print('bad')
    input(1)
        
    
    
