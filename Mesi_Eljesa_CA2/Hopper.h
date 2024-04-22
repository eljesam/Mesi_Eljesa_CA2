//
// Created by biava on 10/04/2024.
//

#ifndef CA2BIANCAVALICEC_HOPPER_H
#define CA2BIANCAVALICEC_HOPPER_H

#include "../../Downloads/Valicec_Bianca_CA2-master/Valicec_Bianca_CA2-master/Bug.h"

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

#endif //CA2BIANCAVALICEC_HOPPER_H
