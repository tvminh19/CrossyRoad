 #include "CGame.h"
 #include "CConsole.h"

 int main(){
    //some setting for console screen
    system("cls");
    SetWindowSize(150, 150);
    SetScreenBufferSize(150, 150);
    DisableCtrButton(0, 0, 1);
    ShowScrollbar(0);
    DisableResizeWindow();
    DisableSelection();

    CGame a;
    int mode = a.drawMenu();
    while (1){
        switch (mode){
            case 0:
                //new game
                break;
            case 1:
                a.loadGame();
                break;
            case 2:
                a.rankings();
                break;
            case 3:
                a.settingsGame();
                break;
            case 4:
                exit(0);
                break;
        }
        mode=a.drawMenu();
    }
     
     return 0;
 }
