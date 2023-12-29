#ifndef GAMECALCULATOR_CALCULATOR_H
#define GAMECALCULATOR_CALCULATOR_H

#include "board.h"
#include "field.h"

class [[maybe_unused]] Calculator : Board {
private:
    static bool checkFields(std::vector<Field> &fields);

    int singleDeckerShipsCount = 0, doubleDeckerShipsCount = 3, threeDeckerShipsCount = 2, fourDeckerShipsCount = 1;

    std::vector<std::vector<int>> probabilityBoard = std::vector<std::vector<int>>();
    std::vector<Field> currentData;
public:
    explicit Calculator(int single_decker_ships_count = 0, int double_decker_ships_count = 3, int three_decker_ships_count = 2, int four_decker_ships_count = 1) : Board() {
        this->singleDeckerShipsCount = single_decker_ships_count;
        this->doubleDeckerShipsCount = double_decker_ships_count;
        this->threeDeckerShipsCount = three_decker_ships_count;
        this->fourDeckerShipsCount = four_decker_ships_count;
    };

    [[maybe_unused]] std::vector<std::vector<int>> calculate();
    [[maybe_unused]] std::pair<int, int> getBestMove();
    [[maybe_unused]] void setShip(int x, int y, bool value);
    [[maybe_unused]] void setShooted(int x, int y, bool value);
    [[maybe_unused]] void setStatus(int x, int y, bool value);

    [[maybe_unused]] void removeSingleDeckerShip();
    [[maybe_unused]] void removeDoubleDeckerShip();
    [[maybe_unused]] void removeThreeDeckerShip();
    [[maybe_unused]] void removeFourDeckerShip();
};

#endif //GAMECALCULATOR_CALCULATOR_H
