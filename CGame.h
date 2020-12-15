#pragma comment(lib, "winmm.lib")
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
    CMap map;
    // bool isRunning = false;
    static bool isMute;
    static int level;
    //position
    int x = 50;
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
    int newGame();
    void loadGame();
    void rankings();
    int settingsGame();
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

    bool loseMenu();
    void pauseMenu();
    void saveGame();
};



#endif // _CGAME_H_