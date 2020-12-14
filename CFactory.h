#ifndef _CFACTORY_H_
#define _CFACTORY_H_

#include "CEnemy.h"
#include <fstream>

class cFactory
{
private:
	Flyweight *flyweight;
public:
	cFactory(int i);
	char* readShapeFile(std::string fileName);
	cEnemy* spawnEnemy(cPosition pos, int direction);
	~cFactory();
};

#endif // !_CFACTORY_H_