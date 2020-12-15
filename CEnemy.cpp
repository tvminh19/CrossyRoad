// #include "CEnemy.h"
// CEnemy::CEnemy(Flyweight* shared_state, cPosition pos, int direction) : shared_state(shared_state), pos(pos), direction(direction) , prePos(pos)
// {
// 	draw();
// }
// bool CEnemy::move(int speed)
// {
// 	this->prePos.x = this->pos.x;
// 	//this->pos.x = this->pos.x + direction * speed * shared_state->defaultSpeed;

// 	//delete old shape
// 	gotoXY(prePos.x, prePos.y);
// 	std::cout << "       \n       \n       ";

// 	// check out of map
// 	if (this->pos.x < 3 || this->pos.x > 101)
// 		return 0;
// 	//draw if not out of map
// 		draw();
// 	return 1;
// }

// void CEnemy::draw()
// {
// 	gotoXY(pos.x, pos.y);
// 	//std::cout << shared_state->shape;
// }

// void CEnemy::makeSound()
// {
// }
