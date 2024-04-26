//
// Created by eljes on 26/04/2024.
//

#include <vector>
#include "Cell.h"
#include "Board.h"
using namespace std;
Board::Board(int width, int height) : grid(height, std::vector<Cell>(width)) {}

Cell Board::getCell(int x, int y) const {
    return grid[y][x];
}

void Board::setCell(int x, int y, const Cell& cell) {
    grid[y][x] = cell;
}

int Board::getWidth() const {
    return grid[0].size();
}

int Board::getHeight() const {
    return grid.size();
}