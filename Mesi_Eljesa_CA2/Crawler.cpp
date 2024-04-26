
#include "Crawler.h"

void Crawler::move() {


    if (isWayBlocked(direction)) {
        while (isWayBlocked(direction)) {

            direction = (rand() % 4 + 1);
        }
    }

    if (direction == 1) {
        if (!isWayBlocked(direction)) {
            position.second--;
        }
    } else if (direction == 2) {
        if (!isWayBlocked(direction)) {
            position.first++;
        }
    } else if (direction == 3) {
        if (!isWayBlocked(direction)) {
            position.second++;
        }
    } else if (direction == 4) {
        if (!isWayBlocked(direction)) {
            position.first--;
        }
    }

    path.push_back(position);
}
