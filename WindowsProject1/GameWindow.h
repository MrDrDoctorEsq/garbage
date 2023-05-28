#pragma once
#include "framework.h"
class GameWindow
{
private:
	static const int MAX_LOADSTRING = 100;
	HINSTANCE hInst;
	LPWSTR lpCmdLine;
	int nCmdShow;
	int ExitCode;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	LRESULT CALLBACK    InternalWndProc(UINT, WPARAM, LPARAM); 
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
	void DrawWindow();
protected:
	HWND hWnd; 
public:
	int GetExitCode() const { return ExitCode; }
	GameWindow(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	virtual ~GameWindow();
	bool Initialize(const wchar_t*  szClassId, const wchar_t* szTitle);
	bool Run();
	virtual void OnPaint(HDC hDC);
	virtual void OnKeyDown(int vkCode);
};
