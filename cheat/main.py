from cheat.gamecalculator import Calculator

if __name__ == "__main__":
    board = Calculator()

    for i in board.calculate():
        print(i)