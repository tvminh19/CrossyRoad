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
        console.gotoXY(c.x - 20, _y++);
        cout << tmp << endl;
    }
    in.close();
}

int CGame::drawMenu() {
    const string mode[5] = { "NEW GAME","LOADING GAME","RANKING","SETTINGS","EXIT" };
    int arrColor[5] = { 12,7,7,7,7 };
    int pos = 0;

    //play music
    if (!isMute) {
        PlaySound(TEXT("source\\audio\\PUBG.wav"), NULL, SND_FILENAME);
    }
    
    //printLogo
    printLogo();

    //print choice
    char key;
    for (int i = 0; i < 5; i++) {
        console->gotoXY(x + 10, y + i);
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
            console->gotoXY(x + 10, y + i);
            console->color(arrColor[i]);
            cout << mode[i] << endl;
        }
    }
    return 0;
}