#include "CGame.h"

//some setting for cgame_
bool CGame::isMute=false;
int CGame::level=1;

CGame::CGame() {
    //
}

CGame::~CGame() {
    //
}

void printLogo() {
    CGame c;
    ifstream in;
    in.open("source\\images\\crossingroad.txt");
    //safe
    if (!in.is_open()) {
        cout << "Cannot open crossingroad.txt";
        exit(0);
    }
    //read
    int _y = c.y - 10;
    while (!in.eof()) {
        string tmp;
        getline(in, tmp);
        gotoXY(c.x - 30, _y++);
        cout << tmp << endl;
    }
    in.close();
}

/* -------------------------------- draw menu ------------------------------- */
int CGame::drawMenu() {
    const string mode[5] = { "NEW GAME  ","LOADING GAME","RANKING","SETTINGS","EXIT" };
    int arrColor[5] = { 12,7,7,7,7 };
    int pos = 0;

    //play MUSIC
    if (!isMute) {
        //PlaySound(TEXT("source\\audio\\PUBG.wav"), NULL, SND_FILENAME);
    }
    
    //printLogo
    printLogo();

    //print choice
    char key;
    for (int i = 0; i < 5; i++) {
        gotoXY(x, y + i);
        setColor(arrColor[i]);
        cout << mode[i] << endl;
    }
    while (key = _getch()) {
        if (key == 'w' && pos > 0) {
            --pos;
        }
        else if (key=='s' && pos<4){
            ++pos;
        }
        else if (key == 'q') {
            exit(0);
        }
        if (key == 13) {
            return pos;
        }
        //reset color
        for (int i = 0; i < 5; ++i) {
            arrColor[i] = 7;
        }
        //coloring mode
        arrColor[pos] = 12;

        //print logo again
        setColor(1 + rand() % 16);
        printLogo();

        //print mode to choose
        for (int i = 0; i < 5; i++) {
            gotoXY(x, y + i);
            setColor(arrColor[i]);
            cout << mode[i] << endl;
        }
    }
    return 0;
}

/* -------------------------------- settings -------------------------------- */
int CGame::settingsGame(){
    system("cls");
    //prepare
    gotoXY(x,y-10);
    int color[3]={12, 7, 7};
    string choose[3]={"MUSIC: ON ", "LEVEL: 1", "EXIT"};
    if (this->isMute){
        choose[0]="MUSIC: OFF";
    }
    else{
        choose[0]="MUSIC: ON ";
    }
    choose[1]="LEVEL: "+to_string(this->level);
    int pos=0;

    //print logo
    printLogo();

    //print choices
    for (int i=0; i<3; ++i){
        gotoXY(x,y+i);
        setColor(color[i]);
        cout<<choose[i]<<endl;
    }

    //choose
    while (char key=_getch()){
        if (key == 'w' && pos > 0) {
            --pos;
        }
        else if (key=='s' && pos<2){
            ++pos;
        }
        else if (key == 'q') {
            exit(0);
        }
        if (key == 13) {

/* ---------------------------------- music --------------------------------- */
            if (pos==0 && choose[0]=="MUSIC: ON "){
                choose[0]="MUSIC: OFF";
                CGame::isMute=true;
            }
            else if (pos==0 && choose[0]=="MUSIC: OFF"){
                choose[0]="MUSIC: ON ";
                CGame::isMute=false;
            }

/* ---------------------------------- level --------------------------------- */
            else if (pos==1){
                string tmp="";
                while(char s=_getch()){
                    if (s=='d' && this->level<7){
                        tmp="LEVEL: ";
                        tmp+=to_string(++this->level);
                        choose[1]=tmp;
                    }
                    else if (s=='a' && this->level>1){
                        string tmp="LEVEL: ";
                        tmp+=to_string(--this->level);
                        choose[1]=tmp;
                    }
                    else if (s==13){
                        break;
                    }
                    
                    //print logo
                    setColor(1 + rand() % 16);
                    printLogo();

                    //print choose setting level
                    gotoXY(x, y + 1);
                    setColor(color[1]);
                    cout << choose[1] << endl;
                }
            }

/* ---------------------------------- exit ---------------------------------- */
            else if (pos==2){
                return this->drawMenu();
            }
        }

        //reset color
        for (int i = 0; i < 3; ++i) {
            color[i] = 7;
        }

        //coloring mode
        color[pos] = 12;

        //print logo again
        setColor(1 + rand() % 16);
        printLogo();

        //print mode to choose
        for (int i = 0; i < 3; i++) {
            gotoXY(x, y + i);
            setColor(color[i]);
            cout << choose[i] << endl;
        }
    }
    return 4;
}

/* -------------------------------- new game -------------------------------- */
int CGame::newGame(){
    /*inside CMap.start
    0. pause game => menu => save->return main menu, continue game, exit.
    1. win up 1 level 
    -1.lose => pause game*/
    int stt=map.startGame(this->level);
    switch(stt){
        case 0:
            map.pauseGame();
            //print menu
            map.continueGame();
            break;
        case 1:
            map.printWin();
            this->level++;
            return this->newGame();
            break;
        case -1:
            if(this->loseMenu()){
                this->level=1;
                return this->newGame();
            }
            else{
                //ask for save game
                this->saveGame();
                return this->drawMenu();
            }
            break;
    }
}

void CGame::loadGame(){
    //load file take the lelel
    //CGame.newGame(int level);
    
}