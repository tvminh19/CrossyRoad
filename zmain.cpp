#include <SFML/Graphics.hpp>
#include <iostream>
// #include "Player.h"
#include "Game.h"

int main(){
    //Init Game engine
	Game game;
	int t = game.runGame();
	std::cout<<t<<std::endl;
}