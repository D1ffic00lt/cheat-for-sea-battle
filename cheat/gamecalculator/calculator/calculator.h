#ifndef GAMECALCULATOR_CALCULATOR_H
#define GAMECALCULATOR_CALCULATOR_H

#include "board.h"

class Calculator : Board {
private:
    static bool checkFields(std::vector<Field> &fields);

    int singleDeckerShipsCount, doubleDeckerShipsCount, threeDeckerShipsCount, fourDeckerShipsCount;

    std::vector<std::vector<int>> probabilityBoard;
    std::vector<Field> currentData{};
    void initBoard();
    void refreshBoard();
public:
    explicit Calculator(int single_decker_ships_count = 0, int double_decker_ships_count = 3, int three_decker_ships_count = 2, int four_decker_ships_count = 1) : Board() {
        this->singleDeckerShipsCount = single_decker_ships_count;
        this->doubleDeckerShipsCount = double_decker_ships_count;
        this->threeDeckerShipsCount = three_decker_ships_count;
        this->fourDeckerShipsCount = four_decker_ships_count;
    };

    std::vector<std::vector<int>> calculate();
    void setShip(int x, int y, bool value);
    void setShooted(int x, int y, bool value);
    void setStatus(int x, int y, bool value, bool clicked = false);

    void setSingleDeckerShip(int value);
    void setDoubleDeckerShip(int value);
    void setThreeDeckerShip(int value);
    void setFourDeckerShip(int value);
};

#endif //GAMECALCULATOR_CALCULATOR_H
