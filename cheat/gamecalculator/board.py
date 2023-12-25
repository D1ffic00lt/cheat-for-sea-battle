from .field import Field


class Board(object):
    def __init__(self):
        self.__board = []
        for _ in range(10):
            self.__board.append([Field() for _ in range(10)])

    @property
    def board(self):
        return self.__board

    def __getitem__(self, item: tuple[[slice, int], [slice, int]]) -> list | Field:
        item1 = item
        item2 = None
        if isinstance(item, tuple):
            item1, item2 = item

        if isinstance(item1, slice):
            if item2 is None:
                return self.__board[item1.start:item1.stop:item1.step]
            if isinstance(item2, slice):
                result_board = []
                for i in self.__board[item1.start:item1.stop:item1.step]:
                    result_board.append(i[item2.start:item2.stop:item2.step])
                return result_board
            result_board = []
            for i in self.__board[item1.start:item1.stop:item1.step]:
                result_board.append(i[item2])
            return result_board
        if item2 is not None:
            if isinstance(item2, slice):
                result_board = []
                for i in self.__board[item1]:
                    result_board.append(i[item2.start:item2.stop:item2])
                return result_board
            return self.__board[item1][item2]
        return self.__board[item1]