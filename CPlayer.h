#ifndef _CPLAYER_H_
#define _CPLAYER_H_
#include "CPosition.h"
class CPlayer{
private:
    CPosition position;
    bool isDead=false;
    char **shape;
    char **emptyShape;
    int width=5, height=3;
public:
    CPlayer();
    void up();
    void down();
    void left();
    void right();
    bool getDeadStt(); //check is dead?
    void setDeadStt(); 
    int getX();
    int getY();
    void sound();
    bool crash(CPosition pos, int _width, int _height);
};

#endif // _CPLAYER_H_