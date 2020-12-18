#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
// #include "Player.h"
#include "Background.h"
#include "TrafficManager.h"
#include "TextItem.h"
#include "CGame.h"

int calcScore(float fTime, int iMoves, int iLives){
	int iTimeScore = (int)(fTime);		// Converts the float time to and int score
	return (iTimeScore + iMoves - iLives * 5) + 1;	// Takes all values to return a score
}

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