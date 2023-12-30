#include "calculator.h"

std::vector<std::vector<int>> Calculator::calculate() {
    for (int y = 0; y < 10; y++) {
        this->probabilityBoard.emplace_back();
        for (int x = 0; x < 10; x++) {
            if (this->singleDeckerShipsCount > 0) {
                this->probabilityBoard[y].push_back(1);
            }
            else {
                this->probabilityBoard[y].push_back(0);
            }
        }
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if ((this->board[y][x].ship) and (not this->board[y][x].shooted)) {
                this->probabilityBoard[y][x] = 0;
                this->board[y][x].status = false;

                if (y != 9) {
                    this->probabilityBoard[y + 1][x] = 100;
                }

                if (y != 0) {
                    this->probabilityBoard[y - 1][x] = 100;
                }

                if (x != 9) {
                    this->probabilityBoard[y][x + 1] = 100;
                }

                if (x != 0) {
                    this->probabilityBoard[y][x - 1] = 100;
                }

            }
            if (this->board[y][x].shooted) {
                this->probabilityBoard[y][x] = 0;
                this->board[y][x].status = false;
                if (y != 9) {
                    this->probabilityBoard[y + 1][x] = 0;
                    this->board[y + 1][x].status = false;
                }

                if (y != 0) {
                    this->probabilityBoard[y - 1][x] = 0;
                    this->board[y - 1][x].status = false;
                }

                if (x != 9) {
                    this->probabilityBoard[y][x + 1] = 0;
                    this->board[y][x + 1].status = false;
                }

                if (x != 0) {
                    this->probabilityBoard[y][x - 1] = 0;
                    this->board[y][x - 1].status = false;
                }

            }
        }
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (not this->board[y][x].status) {
                this->probabilityBoard[y][x] = 0;
                continue;
            }

            if (this->doubleDeckerShipsCount > 0) {
                if (x < 9) {
                    currentData = {};
                    for (int x1 = x; x1 < x + 2; x1++) {
                        currentData.push_back(this->board[y][x1]);
                    }

                    if (Calculator::checkFields(currentData)) {
                        for (int i = 0; i < 2; i++) {
                            this->probabilityBoard[y][x + i] += 1;
                        }
                    }
                }

                if (y < 9) {
                    currentData = {};
                    for (int y1 = y; y1 < y + 2; y1++) {
                        currentData.push_back(this->board[y1][x]);
                    }

                    if (Calculator::checkFields(currentData)) {
                        for (int i = 0; i < 2; i++) {
                            this->probabilityBoard[y + i][x] += 1;
                        }
                    }
                }
            }

            if (this->threeDeckerShipsCount > 0) {
                if (x < 8) {
                    currentData = {};
                    for (int x1 = x; x1 < x + 3; x1++) {
                        currentData.push_back(this->board[y][x1]);
                    }

                    if (Calculator::checkFields(currentData)) {
                        for (int i = 0; i < 3; i++) {
                            this->probabilityBoard[y][x + i] += 1;
                        }
                    }
                }

                if (y < 8) {
                    currentData = {};
                    for (int y1 = y; y1 < y + 2; y1++) {
                        currentData.push_back(this->board[y1][x]);
                    }

                    if (Calculator::checkFields(currentData)) {
                        for (int i = 0; i < 3; i++) {
                            this->probabilityBoard[y + i][x] += 1;
                        }
                    }
                }

            }


            if (this->fourDeckerShipsCount > 0) {
                if (x < 7) {
                    currentData = {};
                    for (int x1 = x; x1 < x + 4; x1++) {
                        currentData.push_back(this->board[y][x1]);
                    }

                    if (Calculator::checkFields(currentData)) {
                        for (int i = 0; i < 4; i++) {
                            this->probabilityBoard[y][x + i] += 1;
                        }
                    }
                }

                if (y < 7) {
                    currentData = {};
                    for (int y1 = y; y1 < y + 4; y1++) {
                        currentData.push_back(this->board[y1][x]);
                    }

                    if (Calculator::checkFields(currentData)) {
                        for (int i = 0; i < 4; i++) {
                            this->probabilityBoard[y + i][x] += 1;
                        }
                    }
                }
            }
        }
    }
    return this->probabilityBoard;
}

std::pair<int, int> Calculator::getBestMove() {
    if (this->probabilityBoard.empty()) {
        this->calculate();
    }
    int best_move = -1;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (best_move < this->probabilityBoard[y][x]) {
                best_move = this->probabilityBoard[y][x];
            }
        }
    }
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (this->probabilityBoard[y][x] == best_move) {
                return std::make_pair(y, x);
            }
        }
    }
    return std::make_pair(0, 0);
}

bool Calculator::checkFields(std::vector<Field> &fields) {
    return std::all_of(fields.begin(), fields.end(), [](const Field &field) {
        return field.status;
    });
}

void Calculator::setShip(int x, int y, bool value) {
    this->board[y][x].ship = value;
}

void Calculator::setShooted(int x, int y, bool value) {
    this->board[y][x].shooted = value;
}

void Calculator::setStatus(int x, int y, bool value) {
    this->board[y][x].status = value;
}

void Calculator::removeSingleDeckerShip() {
    if (this->singleDeckerShipsCount > 0) {
        this->singleDeckerShipsCount--;
    }
}
void Calculator::removeDoubleDeckerShip() {
    if (this->doubleDeckerShipsCount > 0) {
        this->doubleDeckerShipsCount--;
    }
}
void Calculator::removeThreeDeckerShip() {
    if (this->threeDeckerShipsCount > 0) {
        this->threeDeckerShipsCount--;
    }
}
void Calculator::removeFourDeckerShip() {
    if (this->fourDeckerShipsCount > 0) {
        this->fourDeckerShipsCount--;
    }
}