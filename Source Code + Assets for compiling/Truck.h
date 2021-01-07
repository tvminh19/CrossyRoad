#ifndef _TRUCK_H_
#define _TRUCK_H_
#include "Enemy.h"

class Truck: public Enemy{
private:
    //
public:
    Truck();

    void update();

    void makeSound();
};

#endif