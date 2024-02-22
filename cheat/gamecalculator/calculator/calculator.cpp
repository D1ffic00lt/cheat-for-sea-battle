#include "calculator.h"


void Calculator::initBoard() {
    this->probabilityBoard = {};
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
}

void Calculator::refreshBoard() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (this->board[y][x].ship) {
                this->probabilityBoard[y][x] = 0;

                if (y != 9) {
                    if (this->board[y + 1][x].status) {
                        this->probabilityBoard[y + 1][x] = 100;
                    }
                }

                if (y != 0) {
                    if (this->board[y - 1][x].status) {
                        this->probabilityBoard[y - 1][x] = 100;
                    }
                }

                if (x != 9) {
                    if (this->board[y][x + 1].status) {
                        this->probabilityBoard[y][x + 1] = 100;
                    }
                }

                if (x != 0) {
                    if (this->board[y][x - 1].status) {
                        this->probabilityBoard[y][x - 1] = 100;
                    }
                }

            }
            if (this->board[y][x].shooted) {
                this->probabilityBoard[y][x] = 0;
                if (y != 9) {
                    this->probabilityBoard[y + 1][x] = 0;
                }

                if (y != 0) {
                    this->probabilityBoard[y - 1][x] = 0;
                }

                if (x != 9) {
                    this->probabilityBoard[y][x + 1] = 0;
                }

                if (x != 0) {
                    this->probabilityBoard[y][x - 1] = 0;
                }

            }
            if (!this->board[y][x].status) {
                this->probabilityBoard[y][x] = 0;
            }
        }
    }
}

std::vector<std::vector<int>> Calculator::calculate() {
    this->initBoard();
    this->refreshBoard();
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
                            if (this->board[y][x + i].status) {
                                this->probabilityBoard[y][x + i] += 1;
                            }
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
                            if (this->board[y + i][x].status) {
                                this->probabilityBoard[y + i][x] += 1;
                            }
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
                            if (this->board[y][x + i].status) {
                                this->probabilityBoard[y][x + i] += 1;
                            }
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
                            if (this->board[y + i][x].status) {
                                this->probabilityBoard[y + i][x] += 1;
                            }
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
                            if (this->board[y][x + i].status) {
                                this->probabilityBoard[y][x + i] += 1;
                            }
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
                            if (this->board[y + i][x].status) {
                                this->probabilityBoard[y + i][x] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    this->refreshBoard();
    return this->probabilityBoard;
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
//    this->board[y][x].status = !value;
    if (y < 9) {
        if (!this->board[y + 1][x].clicked) {
            this->board[y + 1][x].status = !value;
        }
    }
    if (y > 0) {
        if (!this->board[y - 1][x].clicked) {
            this->board[y - 1][x].status = !value;
        }
    }
    if (x < 9) {
        if (!this->board[y][x + 1].clicked) {
            this->board[y][x + 1].status = !value;
        }
    }
    if (x > 0) {
        if (!this->board[y][x - 1].clicked) {
            this->board[y][x - 1].status = !value;
        }
    }
}

void Calculator::setStatus(int x, int y, bool value, bool clicked) {
    this->board[y][x].status = value;
    this->board[y][x].clicked = clicked;
}

void Calculator::setSingleDeckerShip(int value) {
    this->singleDeckerShipsCount = value;
}

void Calculator::setDoubleDeckerShip(int value) {
    this->doubleDeckerShipsCount = value;
}

void Calculator::setThreeDeckerShip(int value) {
    this->threeDeckerShipsCount = value;
}

void Calculator::setFourDeckerShip(int value) {
    this->fourDeckerShipsCount = value;
}