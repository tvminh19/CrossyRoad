#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CFlyweight.h"
#include "CConsole.h"
struct cPosition
{
	int x, y;
};

class CEnemy
{
private:
	Flyweight * shared_state;
	cPosition pos;
	cPosition prePos;
	int direction;
public:
	CEnemy(Flyweight* shared_state, cPosition pos, int direction);
	bool move(int i);
	void draw();
	void makeSound();
};


#endif // _CENEMY_