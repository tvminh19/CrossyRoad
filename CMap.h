//check lan 4
#ifndef CMAP_H
#define CMAP_H
class CMap {
private:
public:
    CMap();
    ~CMap();
    int startGame(int _level);
    void pauseGame();
    void continueGame();
    void printWin();
    void printLose();
};

#endif // !CMAP_H
