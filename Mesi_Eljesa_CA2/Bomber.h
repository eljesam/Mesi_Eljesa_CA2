
#ifndef MESI_ELJESA_CA2_BOMBER_H
#define MESI_ELJESA_CA2_BOMBER_H
// Bomber class is a child class of Bug class
#include <string>
#include "Bug.h"
// Bomber class inherits all the attributes and methods from Bug class
class Bomber : public Bug {
private:
    bool exploded = false;
public:
    Bomber(int id, pair<int, int> position, int direction, int size) {
        this->id = id;
        this->bugType = "Bomber";
        this->position = position;
        this->direction = direction;
        this->size = size;
        this->alive = true;
    }
    void move() override;



};


#endif //MESI_ELJESA_CA2_BOMBER_H
