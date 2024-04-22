//
// Created by biava on 10/04/2024.
//

#ifndef CA2BIANCAVALICEC_CRAWLER_H
#define CA2BIANCAVALICEC_CRAWLER_H

#include "../../Downloads/Valicec_Bianca_CA2-master/Valicec_Bianca_CA2-master/Bug.h"

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

#endif //CA2BIANCAVALICEC_CRAWLER_H
