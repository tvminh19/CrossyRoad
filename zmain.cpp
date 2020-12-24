#include "Menu.h"

int main(){
    Menu menu;
    switch (menu.drawMenu()){
    //newgame
    case 0:
        menu.newGame();
        break;
    case 1:
        menu.loadGame();
        break;
    case 2:
        menu.rank();
        break;
    case 4:
        menu.music();
        break;
    case 5:
        menu.exit();
        break;
    }
    return 0;
}
