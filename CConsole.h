#ifndef _CCONSOLE_H_
#define _CCONSOLE_H_
#pragma comment(lib, "winmm.lib")
#include <windows.h>

class CConsole {
public:
    void gotoXY(int x, int y);
    void cls();
    void color(int _color);
    void DisableResizeWindow();
    void SetWindowSize(SHORT width, SHORT height);
    void SetScreenBufferSize(SHORT width, SHORT height);
    void DisableCtrButton(bool Close, bool Min, bool Max);
    void ShowScrollbar(BOOL Show);
    void DisableSelection();
};



#endif // _CCONSOLE_