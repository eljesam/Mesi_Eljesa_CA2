

#ifndef MESI_ELJESA_CA2_HOPPER_H
#define MESI_ELJESA_CA2_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength;

public:
    Hopper(int id, pair<int, int> position, Direction direction, int size, int hopLength) {
        this->id = id;
        this->position = position;
        this->direction = direction;
        this->size = size;
        this->alive = true;
        this->hopLength = hopLength;
    }

    void move() override;


};

#endif //MESI_ELJESA_CA2_HOPPER_H
