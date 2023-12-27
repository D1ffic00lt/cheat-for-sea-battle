#include <vector>

#include "board.h"

class Calculator : Board {
    int single_decker_ships_count = 0, double_decker_ships_count = 3, three_decker_ships_count = 2, four_decker_ships_count = 1;
    std::vector<std::vector<int>> probability_board = std::vector<std::vector<int>>();
    std::vector<Field> current_data;

public:
    explicit Calculator(int single_decker_ships_count = 0, int double_decker_ships_count = 3, int three_decker_ships_count = 2, int four_decker_ships_count = 1) : Board() {
        this->single_decker_ships_count = single_decker_ships_count;
        this->double_decker_ships_count = double_decker_ships_count;
        this->three_decker_ships_count = three_decker_ships_count;
        this->four_decker_ships_count = four_decker_ships_count;
    }

    std::vector<std::vector<int>> calculate() {
        for (int y = 0; y < 10; y++) {
            this->probability_board.emplace_back();
            for (int x = 0; x < 10; x++) {
                if (this->single_decker_ships_count > 0) {
                    this->probability_board[y].push_back(1);
                }
                else {
                    this->probability_board[y].push_back(0);
                }
            }
        }
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if ((this->board[y][x].ship) and (not this->board[y][x].shooted)) {
                    this->probability_board[y][x] = 0;
                    this->board[y][x].status = false;

                    if (y != 9) {
                        this->probability_board[y + 1][x] = 100;
                    }

                    if (y != 0) {
                        this->probability_board[y - 1][x] = 100;
                    }

                    if (x != 9) {
                        this->probability_board[y][x + 1] = 100;
                    }

                    if (x != 0) {
                        this->probability_board[y][x - 1] = 100;
                    }

                }
                if (this->board[y][x].shooted) {
                    this->probability_board[y][x] = 0;
                    this->board[y][x].status = false;
                    if (y != 9) {
                        this->probability_board[y + 1][x] = 0;
                        this->board[y + 1][x].status = false;
                    }

                    if (y != 0) {
                        this->probability_board[y - 1][x] = 0;
                        this->board[y - 1][x].status = false;
                    }

                    if (x != 9) {
                        this->probability_board[y][x + 1] = 0;
                        this->board[y][x + 1].status = false;
                    }

                    if (x != 0) {
                        this->probability_board[y][x - 1] = 0;
                        this->board[y][x - 1].status = false;
                    }

                }
            }
        }
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (not this->board[y][x].status) {
                    this->probability_board[y][x] = 0;
                    continue;
                }

                if (this->double_decker_ships_count > 0) {
                    if (x < 9) {
                        current_data = {};
                        for (int x1 = x; x1 < x + 2; x1++) {
                            current_data.push_back(this->board[y][x1]);
                        }

                        if (Calculator::checkFields(current_data)) {
                            for (int i = 0; i < 2; i++) {
                                this->probability_board[y][x + i] += 1;
                            }
                        }
                    }

                    if (y < 9) {
                        current_data = {};
                        for (int y1 = y; y1 < y + 2; y1++) {
                            current_data.push_back(this->board[y1][x]);
                        }

                        if (Calculator::checkFields(current_data)) {
                            for (int i = 0; i < 2; i++) {
                                this->probability_board[y + i][x] += 1;
                            }
                        }
                    }
                }

                if (this->three_decker_ships_count > 0) {
                    if (x < 8) {
                        current_data = {};
                        for (int x1 = x; x1 < x + 3; x1++) {
                            current_data.push_back(this->board[y][x1]);
                        }

                        if (Calculator::checkFields(current_data)) {
                            for (int i = 0; i < 3; i++) {
                                this->probability_board[y][x + i] += 1;
                            }
                        }
                    }

                    if (y < 8) {
                        current_data = {};
                        for (int y1 = y; y1 < y + 2; y1++) {
                            current_data.push_back(this->board[y1][x]);
                        }

                        if (Calculator::checkFields(current_data)) {
                            for (int i = 0; i < 3; i++) {
                                this->probability_board[y + i][x] += 1;
                            }
                        }
                    }

                }


                if (this->four_decker_ships_count > 0) {
                    if (x < 7) {
                        current_data = {};
                        for (int x1 = x; x1 < x + 4; x1++) {
                            current_data.push_back(this->board[y][x1]);
                        }

                        if (Calculator::checkFields(current_data)) {
                            for (int i = 0; i < 4; i++) {
                                this->probability_board[y][x + i] += 1;
                            }
                        }
                    }

                    if (y < 7) {
                        current_data = {};
                        for (int y1 = y; y1 < y + 4; y1++) {
                            current_data.push_back(this->board[y1][x]);
                        }

                        if (Calculator::checkFields(current_data)) {
                            for (int i = 0; i < 4; i++) {
                                this->probability_board[y + i][x] += 1;
                            }
                        }
                    }
                }
            }
        }

        return this->probability_board;
    }
    std::pair<int, int> get_best_move() {
        if (this->probability_board.empty()) {
            calculate();
        }
        int best_move = -1;
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (best_move < this->probability_board[y][x]) {
                    best_move = this->probability_board[y][x];
                }
            }
        }
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (this->probability_board[y][x] == best_move) {
                    return std::make_pair(y, x);
                }
            }
        }
        return std::make_pair(0, 0);
    }

private:
    static bool checkFields(std::vector<Field> &fields){
        for (Field &field : fields) {
            if (not field.status) {
                return false;
            }
        }
        return true;
    }
};
