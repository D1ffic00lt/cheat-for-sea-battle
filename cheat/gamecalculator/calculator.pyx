from libcpp.vector cimport vector
from libcpp.pair cimport pair

cdef extern from "./calculator/calculator.cpp":
    cdef cppclass Field:
        pass

    cdef cppclass Board:
        pass

    cdef cppclass Calculator(Board):
        Calculator(int, int, int, int)
        vector[vector[int]] calculate()
        pair[int, int] get_best_move()

cdef class PyCalculator:
    cdef Calculator *c_calculator

    def __cinit__(self, int single_decker_ships_count=0, int double_decker_ships_count=3, int three_decker_ships_count=2, int four_decker_ships_count=1):
        self.c_calculator = new Calculator(single_decker_ships_count, double_decker_ships_count, three_decker_ships_count, four_decker_ships_count)

    def calculate(self):
        cdef vector[vector[int]] result
        result = self.c_calculator.calculate()
        return [[result[i][j] for j in range(len(result[i]))] for i in range(len(result))]

    def get_best_move(self):
        cdef pair[int, int] move
        move = self.c_calculator.get_best_move()
        return move.first, move.second
