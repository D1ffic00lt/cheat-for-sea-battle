cmake_minimum_required(VERSION 3.24)
project(gamecalculator)

set(CMAKE_CXX_STANDARD 14)

include_directories(calculator)

add_executable(gamecalculator
        calculator/board.h
        calculator/calculator.cpp
        calculator/field.h)
