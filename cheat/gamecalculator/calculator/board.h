#ifndef GAMECALCULATOR_BOARD_H
#define GAMECALCULATOR_BOARD_H
#include <vector>

#include "field.h"

class Board {
public:
    Board();
    std::vector<std::vector<Field>> board;
};

Board::Board() {
    for (int y = 0; y < 10; y++) {
        board.emplace_back();
        for (int x = 0; x < 10; x++) {
            board[y].push_back(*new Field());
        }
    }
}

#endif //GAMECALCULATOR_BOARD_H
