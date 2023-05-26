#include "Tetris.h"


Tetris::Tetris(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
	: GameWindow(hInstance, lpCmdLine, nCmdShow)
	, background(L"texture2.bmp")
	, glassBackground(L"texture.bmp")
{
	hBackground = CreatePatternBrush(background.GetHBitmap());
	hGlassBackground = CreatePatternBrush(glassBackground.GetHBitmap());
	hGlassWall = CreateSolidBrush(RGB(20, 20, 0));
}
Tetris::~Tetris()
{
	DeleteObject(hBackground);
	DeleteObject(hGlassBackground);
	DeleteObject(hGlassWall);
}

void Tetris::OnPaint(HDC hDC)
{
	RECT wndSize;
	GetClientRect(hWnd, &wndSize);
	FillRect(hDC, &wndSize, hBackground);
	int glassSizeX = XSize * (RowsCount + 2);
	int glassSizeY = YSize * (ColumnsCount + 1);
	int x1 = ((wndSize.right - wndSize.left) - glassSizeX) / 2;
	int y1 = (wndSize.bottom - wndSize.top) - glassSizeY;
	int x2 = glassSizeX + x1;
	int y2 = glassSizeY + y1;
	RECT GlassRect;
	SetRect(&GlassRect, x1, y1, x2, y2);
	FillRect(hDC, &GlassRect, hGlassBackground);
	RECT walls[] = 
	{
		{x1, y1, x1 + XSize, y2},
		{x2 - XSize, y1, x2, y2},
		{x1, y2 - YSize, x2, y2}
	};
	for (const RECT& wall : walls)
	{
		FillRect(hDC, &wall, hGlassWall);
	}
	InvalidateRect(hWnd, &wndSize, false);
}