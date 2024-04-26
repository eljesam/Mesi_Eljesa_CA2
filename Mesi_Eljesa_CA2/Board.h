//
// Created by eljes on 26/04/2024.
//

#ifndef MESI_ELJESA_CA2_BOARD_H
#define MESI_ELJESA_CA2_BOARD_H


#include <vector>
#include "Cell.h"

class Board {
private:
    std::vector<std::vector<Cell>> grid;
public:
    Board(int width, int height);

    Cell getCell(int x, int y) const;

    void setCell(int x, int y, const Cell& cell);

    int getWidth() const;

    int getHeight() const;
};

#endif //MESI_ELJESA_CA2_BOARD_H
