 #include "CGame.h"
 #include "CConsole.h"

 int main(){
     //some setting for console screen
     CConsole console;
     console.SetWindowSize(150, 150);
     console.SetScreenBufferSize(150, 150);
     console.DisableCtrButton(0, 0, 1);
     console.ShowScrollbar(0);
     console.DisableResizeWindow();
     console.DisableSelection();


     CGame a;
     a.drawMenu();

     
     return 0;
 }
