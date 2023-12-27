from cheat.gamecalculator import Calculator

if __name__ == "__main__":
    board = Calculator()

    print(board.get_best_move())
    for i in range(10):
        print(board.probability_board[i])