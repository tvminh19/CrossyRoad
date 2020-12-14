#pragma once

class Coor {
public:
    int x, y;
    Coor(int m, int n) { x = n; y = m; };
};

class CPlayer {
private:
    Coor co;
    bool mState; //die or live
public:
    CPlayer();
    CPlayer(int x, int y);
    void Up();
    void Left();
    void Right();
    void Down();
    bool isFinished();
    bool isDead();
    bool isImpact(const CEnemy*);
};

