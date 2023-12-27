from .board import Board
from .field import Field


class Calculator(Board):
    def __init__(self,
                 single_decker_ships_count: int = 0,
                 double_decker_ships_count: int = 3,
                 three_decker_ships_count: int = 2,
                 four_decker_ships_count: int = 1
                 ):
        super().__init__()
        self.four_decker_ships_count = four_decker_ships_count
        self.three_decker_ships_count = three_decker_ships_count
        self.double_decker_ships_count = double_decker_ships_count
        self.single_desk_ships_count = single_decker_ships_count
        self.probability_board = []

    @staticmethod
    def check_fields(fields):
        if isinstance(fields[0], Field):
            for i in range(len(fields)):
                if fields[i].status is False:
                    return False
            return True
        for i in range(len(fields)):
            for j in range(len(fields[i])):
                if fields[i][j].status is False:
                    return False
        return True

    def calculate(self):
        self.probability_board = [
            [
                1 if self.single_desk_ships_count != 0 else 0
                for _ in range(10)
            ]
            for _ in range(10)
        ]
        for x in range(10):
            for y in range(10):
                if self[y, x].ship and not self[y, x].shoot:
                    self.probability_board[y][x] = 0
                    self.board[y][x].status = False
                    if y != 9:
                        self.probability_board[y + 1][x] = 100
                    if y != 0:
                        self.probability_board[y - 1][x] = 100
                    if x != 9:
                        self.probability_board[y][x + 1] = 100
                    if x != 0:
                        self.probability_board[y][x - 1] = 100
                #  game with ships
                if self[y, x].shoot:
                    self.probability_board[y][x] = 0
                    self.board[y][x].status = False
                    if y != 9:
                        self.probability_board[y + 1][x] = 0
                        self.board[y + 1][x].status = False
                    if y != 0:
                        self.probability_board[y - 1][x] = 0
                        self.board[y - 1][x].status = False
                    if x != 9:
                        self.probability_board[y][x + 1] = 0
                        self.board[y][x + 1].status = False
                    if x != 0:
                        self.probability_board[y][x - 1] = 0
                        self.board[y][x - 1].status = False

        for x in range(10):
            for y in range(10):
                if not self[y, x].status:
                    self.probability_board[y][x] = 0
                    continue
                #  default game
                if self.double_decker_ships_count > 0:
                    if self.check_fields(self[y, x:x + 2]) and x < 9:
                        for i in range(0, 2):
                            self.probability_board[y][x + i] += 1
                    if self.check_fields(self[y:y + 2, x]) and y < 9:
                        for i in range(0, 2):
                            self.probability_board[y + i][x] += 1

                if self.three_decker_ships_count > 0:
                    if self.check_fields(self[y, x:x + 3]) and x < 8:
                        for i in range(0, 3):
                            self.probability_board[y][x + i] += 1
                    if self.check_fields(self[y:y + 3, x]) and y < 8:
                        for i in range(0, 3):
                            self.probability_board[y + i][x] += 1

                if self.four_decker_ships_count > 0:
                    if self.check_fields(self[y, x:x + 4]) and x < 7:
                        for i in range(0, 4):
                            self.probability_board[y][x + i] += 1
                    if self.check_fields(self[y:y + 4, x]) and y < 7:
                        for i in range(0, 4):
                            self.probability_board[y + i][x] += 1

        return self.probability_board

    def get_best_move(self):
        if not self.probability_board:
            self.calculate()
        best_move = max(max(self.probability_board))
        for y in range(len(self.probability_board)):
            for x in range(len(self.probability_board[y])):
                if self.probability_board[y][x] == best_move:
                    return x, y
