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
// int CGame::newGame(){
//     /*inside CMap.start
//     0. pause game => menu => save->return main menu, continue game, exit.
//     1. win up 1 level 
//     -1.lose => pause game*/
//     int stt=map.startGame(this->level);
//     switch(stt){
//         case 0:
//             map.pauseGame();
//             //print menu
//             map.continueGame();
//             break;
//         case 1:
//             map.printWin();
//             this->level++;
//             return this->newGame();
//             break;
//         case -1:
//             if(this->loseMenu()){
//                 this->level=1;
//                 return this->newGame();
//             }
//             else{
//                 //ask for save game
//                 this->saveGame();
//                 return this->drawMenu();
//             }
//             break;
//     }
//     return 0;
// }

struct user{
    string name;
    int level;
};

void loadFile(ifstream& in, vector<user>& tmp){
    string a;
    int level;
    while (!in.eof()){
        user k;
        getline(in, k.name);
        in>>k.level;
        in.ignore(100,'\n');
        tmp.push_back(k);
    }
}

//create menu
auto createMenu(string nameOfMenu, string str[], int n){
	int x=50;
	int y=15;
	int pos=0;
	//create array of color
	int *color=new int[n];
	
	//set color to while
	for(int i=1; i<n; ++i){
		color[i]=7;
	}
	color[0]=12;
	//print menu
	gotoXY(x,y-2);
	cout<<"["<<nameOfMenu<<"]\n";
	for(int i=0; i<n; ++i){
		setColor(color[i]);
		gotoXY(x,y+i);
		cout<<str[i];
	}
	//input key
	while(char s=_getch()){
		if(s=='w' && pos>0){
			pos--;
		}
		else if(s=='s' && pos<n-1){
			pos++;
		}
		else if(s=='q'){
			exit(0);
		}
		//s='enter'
		else if(s==13){
			return str[pos];
		}
		
		//reset color
		for(int i=0; i<n; ++i){
		    color[i]=7;
		}
		
		//mark the choice
		color[pos]=12;
		
		//print again
		for(int i=0; i<n; ++i){
            setColor(color[i]);
			gotoXY(x,y+i);
			cout<<str[i];
		}
	}
	delete[] color;
}

int CGame::loadGame(){
    system("cls");
    printLogo();
    //load file take the lelel
    //CGame.newGame(int level);
    vector<user> listUsers;
    ifstream in;
    in.open("source\\user.txt");
    if (in.is_open()){
        string a;
        int b;
        loadFile(in, listUsers);
        in.close();
    }
    else{
        cout<<"can not open user.txt.\n";
        exit(0);
    }

    vector<user> tmp;
    if(listUsers.size()>5){
        for(int i=0; i<5; ++i){
            tmp.push_back(listUsers.back());
            listUsers.pop_back();
        }
        listUsers.clear();
        listUsers=tmp;
    }

    gotoXY(x,y-2);
    cout<<"[LOADING GAME].\n";
    int* color=new int[listUsers.size()];
    for(int i=0;i<listUsers.size(); ++i){
        color[i]=7;
    }
    color[0]=12;
    int pos=0;
    for (int i=0; i<listUsers.size(); i++){
        gotoXY(x,y+i);
        setColor(color[i]);
        cout<<"["<<i<<"]. "<<listUsers[i].name<<" - "<<listUsers[i].level<<endl;
    }
    while(char t=_getch()){
        for(int i=0; i<listUsers.size(); ++i){
            color[i]=7;
        }
        if (t=='w' && pos>0){
            pos--;
        }
        else if (t=='s' && pos<listUsers.size()-1){
            pos++;
        }
        else if (t=='q'){
            exit(0);
        }
        else if (t==13){
            this->level=listUsers[pos].level;
            //return newGame();
            return 0;
        }
        color[pos]=12;
        for (int i=0; i<listUsers.size(); i++){
            gotoXY(x,y+i);
            setColor(color[i]);
            cout<<"["<<i<<"]. "<<listUsers[i].name<<" - "<<listUsers[i].level<<endl;
        }
    }
    delete[] color;
    return 0;
}