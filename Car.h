#ifndef _CAR_H_
#define _CAR_H_
#include "Enemy.h"

class Car: public Enemy{
private:
    
public:
    Car();

    void update();

    void makeSound();
};

#endif