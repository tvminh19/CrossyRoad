// #include "CFactory.h"
// cFactory::cFactory(int i)
// {
// 	//get the name of enemy
// 	std::string fileName;
// 	int speed = 0;
// 	switch (i)
// 	{
// 	case 0:
// 		fileName = "cCar";
// 		speed = 2;
// 		break;
// 	default:
// 		std::cout << std::endl << std::endl << "cannot create Factory["<< i <<"]";;
// 		exit(0);
// 		break;
// 	}

// 	//open the file and get the shape
// 	//initiallize flyweight
// 	flyweight = new Flyweight(readShapeFile(fileName), fileName + ".wav", speed);
// }

// char* cFactory::readShapeFile(std::string fileName)
// {
// 	std::ifstream fin;
// 	char* a = new char[50];
// 	fin.open("source/images" + fileName + ".txt");
// 	if (fin.is_open())
// 	{
// 		int counter = 0;
// 		while (!fin.eof())
// 		{
// 			fin.get(a[counter]);
// 			++counter;
// 		}
// 		a[counter] = '\0';
// 		fin.close();
// 	}
// 	else
// 	{
// 		std::cout << std::endl << std::endl << "cannot open " << fileName << ".txt";
// 		delete[]a;
// 		exit(0);
// 	}
// 	return a;
// }


// cEnemy* cFactory::spawnEnemy(cPosition pos, int direction)
// {
// 	cEnemy* tmp = new cEnemy(flyweight, pos, direction);
// 	return tmp;
// }

// cFactory::~cFactory()
// {
// 	delete flyweight;
// }