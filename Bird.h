#ifndef _CBIRD_H_
#define _CBIRD_H_
#include "Enemy.h"

class Bird: public Enemy{
private:
    //
public:
    Bird();

    void update();

    void makeSound();
};

#endif