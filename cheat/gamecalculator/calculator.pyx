from libcpp.vector cimport vector
from libcpp.pair cimport pair

cdef extern from "./calculator/calculator.h":
    cdef cppclass Calculator:
        Calculator(int, int, int, int)
        vector[vector[int]] calculate()
        pair[int, int] getBestMove()
        void setShip(int, int, bint)
        void setShooted(int, int, bint)
        void setStatus(int, int, bint)
        void removeSingleDeckerShip()
        void removeDoubleDeckerShip()
        void removeThreeDeckerShip()
        void removeFourDeckerShip()

cdef extern from "./calculator/calculator.cpp":
    pass

cdef class PyCalculator:
    cdef Calculator *c_calculator

    def __cinit__(self, int singleDeckerShipsCount=0, int doubleDeckerShipsCount=3, int threeDeckerShipsCount=2, int fourDeckerShipsCount=1):
        self.c_calculator = new Calculator(singleDeckerShipsCount, doubleDeckerShipsCount, threeDeckerShipsCount, fourDeckerShipsCount)

    def calculate(self):
        cdef vector[vector[int]] result
        result = self.c_calculator.calculate()
        return tuple([tuple([result[i][j] for j in range(len(result[i]))]) for i in range(len(result))])

    def get_best_move(self):
        cdef pair[int, int] move
        move = self.c_calculator.getBestMove()
        return move.first, move.second

    def set_ship(self, int y, int x, bint value):
        self.c_calculator.setShip(y, x, value)

    def set_shooted(self, int y, int x, bint value):
        self.c_calculator.setShooted(y, x, value)

    def set_status(self, int y, int x, bint value):
        self.c_calculator.setStatus(y, x, value)

    def remove_single_decker_ship(self):
        self.c_calculator.removeSingleDeckerShip()

    def remove_double_decker_ship(self):
        self.c_calculator.removeDoubleDeckerShip()
    def remove_three_decker_ship(self):
        self.c_calculator.removeThreeDeckerShip()
    def remove_four_decker_ship(self):
        self.c_calculator.removeFourDeckerShip()
