#ifndef _CGAME_H_
#define _CGAME_H_

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "CMap.h"
#include "CConsole.h"
using namespace std;

class CGame {
private:
    //CMap map;
    CConsole* console = nullptr;
    bool isRunning = false;
    bool isMute = false;
    int level = 1;
    //position
    int x = 40;
    int y = 15;
public:
    CGame();
    ~CGame();
    //before start game
    /*0. NEW GAME
      1. LOADING GAME
      2. RANKING
      3. SETTINGS
      4. EXIT*/
    int drawMenu();
    void newGame();
    void loadGame();
    void rankings();
    void settingsGame();
    void audioSettings(bool& mode);
    void levelSettings(int& _level);
    void exitGame();

    //while running game
    void pauseGame();
    void gameOver();
    void loadingEffects();
    void upOneLevel();
    void downOneLevel();

    //other supporting function
    friend void printLogo();
};



#endif // _CGAME_H_