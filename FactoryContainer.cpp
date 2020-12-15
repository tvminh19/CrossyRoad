// #include "FactoryContainer.h"

// //Singleton
// FactoryContainer::FactoryContainer() : FactoryNumber(1)
// {
// 	//create factories
// 	FactoryList = new cFactory* [FactoryNumber];
// 	for (int i = 0; i < FactoryNumber; ++i)
// 	{
// 		FactoryList[i] = new cFactory(i);
// 	}
// }
// FactoryContainer::~FactoryContainer()
// {
// 	//cleaning factories
// 	for (int i = 0; i < FactoryNumber; ++i)
// 	{
// 		delete FactoryList[i];
// 	}
// 	delete FactoryList;
// }

// //Factories
// cFactory* FactoryContainer::getFactory(const std::string& a)
// {
// 	if (a == "cCar")
// 		return FactoryList[0];
// 	std::cout << std::endl << std::endl << "Cannot get the factory: "<< a <<", check the code again please...." << std::endl;
// 	exit(0);
// }

