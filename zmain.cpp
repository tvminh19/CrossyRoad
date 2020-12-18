#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
// #include "Player.h"
#include "Background.h"
#include "TrafficManager.h"
#include "TextItem.h"
#include "CGame.h"

int main(){
    //Init Game engine
	CGame game;

	//Game loop
	while (game.isRunning())
	{
		//Update
		game.update();

		//Render
		game.render();
	}
}