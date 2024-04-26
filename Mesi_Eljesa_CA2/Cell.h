//
// Created by eljes on 26/04/2024.
//

#ifndef MESI_ELJESA_CA2_CELL_H
#define MESI_ELJESA_CA2_CELL_H
#include "Bug.h"
#include <memory>
#include <stdexcept>

class Cell {
private:
    std::shared_ptr<Bug> bug;
public:
    Cell() : bug(nullptr) {}

    // Check if the cell is empty
    bool isEmpty() const {
        return bug == nullptr;
    }

    // Add a bug to the cell
    void addBug(Bug newBug);

    // Remove the bug from the cell
    void removeBug() {
        bug.reset();
    }

    // Get a copy of the bug in the cell
    [[maybe_unused]] [[nodiscard]] shared_ptr<Bug> getBug() const;

    void addBug(shared_ptr<Bug> newBug);
};

void Cell::addBug(std::shared_ptr<Bug> newBug) {
    bug = newBug;
}

std::shared_ptr<Bug> Cell::getBug() const {
    if (bug) {
        return bug;
    } else {
        throw std::runtime_error("No bug in cell");
    }
}

#endif //MESI_ELJESA_CA2_CELL_H
