#ifndef _CPOSITION_H_
#define _CPOSITION_H_

class CPosition{
private:
    int x=0;
    int y=0;
public:
    int getX();
    int getY();
    CPosition getPosition();
    void setX(int _x);
    void setY(int _y);
    void setPosition(int _x, int _y);
};










#endif //