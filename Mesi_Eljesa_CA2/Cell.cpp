#include "Cell.h"

void Cell::addBug(std::shared_ptr<Bug> newBug) {
    bug = std::move(newBug);
}

std::shared_ptr<Bug> Cell::getBug() const {
    if (bug) {
        return bug;
    } else {
        throw std::runtime_error("No bug in cell");
    }
}
