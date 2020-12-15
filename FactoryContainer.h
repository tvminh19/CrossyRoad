#ifndef _CSINGLETON_H_
#define _CSINGLETON_H_

#include "CFactory.h"

class FactoryContainer
{
private:
	//Factory
	int FactoryNumber;
	cFactory** FactoryList;

	//Singleton
	static FactoryContainer* pointer;
	
public:
	//Factory
	cFactory* getFactory(const std::string& a);
	FactoryContainer();
	~FactoryContainer();
};



#endif // !_CSINGLETON_H_