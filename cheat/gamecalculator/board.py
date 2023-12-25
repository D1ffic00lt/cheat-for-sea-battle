from .field import Field


class Board(object):
    def __init__(self):
        self.__board = []
        for _ in range(10):
            self.__board.append([Field() for _ in range(10)])

    @property
    def board(self):
        return self.__board
