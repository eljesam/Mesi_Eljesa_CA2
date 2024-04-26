
#include "Hopper.h"

int Hopper::getHopLength() const {
    return hopLength;
}


void Hopper::move() {


    if (isWayBlocked(direction)) {
        while (isWayBlocked(direction)) {

            direction = (rand() % 4 + 1);
        }
    }

    int distance = getHopLength();

    if (direction == 1) {
        for (int i = 0; i < distance; i++) {
            if (isWayBlocked(direction)) {
                break;
            }
            position.second--;
        }
    } else if (direction == 2) {
        for (int i = 0; i < distance; i++) {
            if (isWayBlocked(direction)) {
                break;
            }
            position.first++;
        }
    } else if (direction == 3) {
        for (int i = 0; i < distance; i++) {
            if (isWayBlocked(direction)) {
                break;
            }
            position.second++;
        }
    } else if (direction == 4) {
        for (int i = 0; i < distance; i++) {
            if (isWayBlocked(direction)) {
                break;
            }
            position.first--;
        }
    }

    path.push_back(position);
}