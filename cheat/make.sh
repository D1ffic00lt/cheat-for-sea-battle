#!/bin/bash

[ ! -e "./gamecalculator/calculator.cpp" ] || rm "./gamecalculator/calculator.cpp"

find . -name "*.so" -type f -delete

python3.11 setup.py build_ext -b builded_calculator

#mv ./gamecalculator/*.cpp ./gamecalculator/calculator/
mv ./builded_calculator/ ./gamecalculator/builded_calculator/