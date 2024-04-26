

#ifndef MESI_ELJESA_CA2_CELL_H
#define MESI_ELJESA_CA2_CELL_H
#include "Bug.h"
#include <memory>
#include <stdexcept>
#include <utility>

class Cell {
private:
    std::shared_ptr<Bug> bug;
public:
    Cell() : bug(nullptr) {}

    // Check if the cell is empty
    [[nodiscard]] bool isEmpty() const {
        return bug == nullptr;
    }

    // Add a bug to the cell
    void addBug(std::shared_ptr<Bug> newBug);

    // Remove the bug from the cell
    void removeBug() {
        bug.reset();
    }

    // Get a copy of the bug in the cell
    [[nodiscard]] std::shared_ptr<Bug> getBug() const;
};
#endif //MESI_ELJESA_CA2_CELL_H
