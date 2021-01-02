#include "Menu.h"

int main() {
    Menu menu;
    switch (menu.drawMenu()) {
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
    case 3:
        menu.music();
        break;
    case 4:
        menu.exit_game();
        break;
    default:
        break;
    }

    return 0;
}

