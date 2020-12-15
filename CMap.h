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
};

#endif // !CMAP_H
