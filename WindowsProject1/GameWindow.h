#pragma once
#include "framework.h"
class GameWindow
{
private:
	static const int MAX_LOADSTRING = 100;
	static HINSTANCE hInst;
	LPWSTR lpCmdLine;
	int nCmdShow;
	int ExitCode;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
public:
	int GetExitCode() { return ExitCode; }
	GameWindow(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	~GameWindow();
	bool Initialize(const wchar_t*  szClassId, const wchar_t* szTitle);
	bool Run();
};
