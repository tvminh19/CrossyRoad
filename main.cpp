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
    switch (mode){
        case 1:
        case 2:
        case 3:
            while (a.settingsGame()==3){}
            break;
        case 4:
            exit(0);
            break;
    }

     
     return 0;
 }
