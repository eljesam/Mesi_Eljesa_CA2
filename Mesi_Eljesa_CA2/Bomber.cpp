#include "Bomber.h"

void Bomber::move() {
    if(isWayBlocked(direction)){
        while(isWayBlocked(direction)){
            direction = (rand()% 4+1);
        }
    }
    if (alive) {
        if (direction == 1) {
            if(!isWayBlocked(direction)){
                if(position.first == 0 && position.second == 0){
                    position.second++;
                }
                else{
                    position.second--;
                }
            }
        } else if (direction == 2) {
            if(!isWayBlocked(direction)){
                if(position.first == 9 && position.second == 0){
                    position.first--;
                }
                else{
                    position.first++;
                }
            }
        } else if (direction == 3) {
            if(!isWayBlocked(direction)){
                if(position.first == 9 && position.second == 9){
                    position.second--;
                }
                else{
                    position.second++;
                }
            }
        } else if (direction == 4) {
            if(!isWayBlocked(direction)){
                if(position.first == 0 && position.second == 9){
                    position.first++;
                }
                else{
                    position.first--;
                }
            }
        }
        else if(direction == 1){
            if(isWayBlocked(direction)){
                exploded = true;
            }
        }
        else if(direction == 2){
            if(isWayBlocked(direction)){
                exploded = true;
            }
        }
        else if(direction == 3){
            if(isWayBlocked(direction)){
                exploded = true;
            }
        }
        else if(direction == 4){
            if(isWayBlocked(direction)){
                exploded = true;
            }
        }

    }
    path.push_back(position);
}
