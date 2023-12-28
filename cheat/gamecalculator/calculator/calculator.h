#ifndef GAMECALCULATOR_CALCULATOR_H
#define GAMECALCULATOR_CALCULATOR_H

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "board.h"
#include "field.h"

class Calculator : Board {
private:
    static bool checkFields(std::vector<Field> &fields);

    int single_decker_ships_count = 0, double_decker_ships_count = 3, three_decker_ships_count = 2, four_decker_ships_count = 1;

    std::vector<std::vector<int>> probability_board = std::vector<std::vector<int>>();
    std::vector<Field> current_data;
public:
    explicit Calculator(int single_decker_ships_count = 0, int double_decker_ships_count = 3, int three_decker_ships_count = 2, int four_decker_ships_count = 1) : Board() {
        this->single_decker_ships_count = single_decker_ships_count;
        this->double_decker_ships_count = double_decker_ships_count;
        this->three_decker_ships_count = three_decker_ships_count;
        this->four_decker_ships_count = four_decker_ships_count;
    };

    std::vector<std::vector<int>> calculate();
    std::pair<int, int> get_best_move();
    void set_ship(int x, int y, bool value);
    void set_shooted(int x, int y, bool value);
    void set_status(int x, int y, bool value);

    void remove_single_decker_ship();
    void remove_double_decker_ship();
    void three_single_decker_ship();
    void four_single_decker_ship();
};

#endif
#endif //GAMECALCULATOR_CALCULATOR_H
