#include "CGame.h"

CGame::CGame() {
    //
}

CGame::~CGame() {
    delete console;
}

void printLogo() {
    CGame c;
    CConsole console;
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
        console.gotoXY(c.x - 30, _y++);
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
        console->gotoXY(x, y + i);
        console->color(arrColor[i]);
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
        console->color(1 + rand() % 16);
        printLogo();

        //print mode to choose
        for (int i = 0; i < 5; i++) {
            console->gotoXY(x, y + i);
            console->color(arrColor[i]);
            cout << mode[i] << endl;
        }
    }
    return 0;
}

/* -------------------------------- settings -------------------------------- */
int CGame::settingsGame(){
    system("cls");
    //prepare
    console->gotoXY(x,y-10);
    int color[3]={12, 7, 7};
    string choose[3]={"MUSIC: ON ", "LEVEL: 1", "EXIT"};
    int pos=0;

    //print logo
    printLogo();

    //print choices
    for (int i=0; i<3; ++i){
        console->gotoXY(x,y+i);
        console->color(color[i]);
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
                this->isMute=false;
            }
            else if (pos==0 && choose[0]=="MUSIC: OFF"){
                choose[0]="MUSIC: ON ";
                this->isMute=true;
            }

/* ---------------------------------- level --------------------------------- */
            else if (pos==1){
                string tmp="";
                while(char s=_getch()){
                    if (s=='=' && this->level<7){
                        tmp="LEVEL: ";
                        tmp+=to_string(++this->level);
                        choose[1]=tmp;
                    }
                    else if (s=='-' && this->level>1){
                        string tmp="LEVEL: ";
                        tmp+=to_string(--this->level);
                        choose[1]=tmp;
                    }
                    else if (s==13){
                        break;
                    }
                    
                    //print logo
                    console->color(1 + rand() % 16);
                    printLogo();

                    //print choose setting level
                    console->gotoXY(x, y + 1);
                    console->color(color[1]);
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
        console->color(1 + rand() % 16);
        printLogo();

        //print mode to choose
        for (int i = 0; i < 3; i++) {
            console->gotoXY(x, y + i);
            console->color(color[i]);
            cout << choose[i] << endl;
        }
    }
    return 4;
}