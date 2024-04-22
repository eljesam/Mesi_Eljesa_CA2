

#ifndef MESI_ELJESA_CA2_CRAWLER_H
#define MESI_ELJESA_CA2_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, pair<int, int> position, Direction direction,int size)
    {
        this->id = id;
        this->position = position;
        this->direction = direction;
        this->size = size;
        this->alive = true;
    }

    void move() override;

};

#endif //MESI_ELJESA_CA2_CRAWLER_H
