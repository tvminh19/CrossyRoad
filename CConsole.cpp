#include "CConsole.h"

void CConsole::gotoXY(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(h, c);
}

void CConsole::color(int _color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _color);
}

void CConsole::cls()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void CConsole::DisableResizeWindow() {
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void CConsole::SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void CConsole::SetScreenBufferSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}

void CConsole::DisableCtrButton(bool Close, bool Min, bool Max)
{
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

void CConsole::ShowScrollbar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}

void CConsole::DisableSelection(){
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}