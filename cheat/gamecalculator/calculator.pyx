from libcpp.vector cimport vector
from libcpp.pair cimport pair

cdef extern from "./calculator/calculator.h":
    cdef cppclass Calculator:
        Calculator(int, int, int, int)
        vector[vector[int]] calculate()
        void setShip(int, int, bint)
        void setShooted(int, int, bint)
        void setStatus(int, int, bint, bint)
        void setSingleDeckerShip(int)
        void setDoubleDeckerShip(int)
        void setThreeDeckerShip(int)
        void setFourDeckerShip(int)

cdef extern from "./calculator/calculator.cpp":
    pass

cdef class PyCalculator:
    cdef Calculator *c_calculator

    def __cinit__(self, int single_decker_ships_count=0, int double_decker_ships_count=3, int three_decker_ships_count=2, int four_decker_ships_count=1):
        self.c_calculator = new Calculator(single_decker_ships_count, double_decker_ships_count, three_decker_ships_count, four_decker_ships_count)

    def calculate(self):
        cdef vector[vector[int]] result
        result = self.c_calculator.calculate()
        return tuple([tuple([result[i][j] for j in range(len(result[i]))]) for i in range(len(result))])

    def set_ship(self, int x, int y, bint value):
        self.c_calculator.setShip(x, y, value)

    def set_shooted(self, int x, int y, bint value):
        self.c_calculator.setShooted(x, y, value)

    def set_status(self, int x, int y, bint value, bint clicked = False):
        self.c_calculator.setStatus(x, y, value, clicked)

    def set_single_decker_ship(self, int value):
        self.c_calculator.setSingleDeckerShip(value)

    def set_double_decker_ship(self, int value):
        self.c_calculator.setDoubleDeckerShip(value)

    def set_three_decker_ship(self, int value):
        self.c_calculator.setThreeDeckerShip(value)

    def set_four_decker_ship(self, int value):
        self.c_calculator.setFourDeckerShip(value)
