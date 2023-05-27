#include "Tetris.h"


Tetris::Tetris(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
	: GameWindow(hInstance, lpCmdLine, nCmdShow)
	, background(L"texture2.bmp")
	, glassBackground(L"texture.bmp")
{
	hBackground = CreatePatternBrush(background.GetHBitmap());
	hGlassBackground = CreatePatternBrush(glassBackground.GetHBitmap());
	hGlassWall = CreateSolidBrush(RGB(20, 20, 20));
	hCube = CreateSolidBrush(RGB(0, 64, 0));
	Figures[0] = Figure(FigureOffset(-1, 0), FigureOffset(0, 1), FigureOffset(1, 1));
	Figures[1] = Figure(FigureOffset(0, 1), FigureOffset(1, 0), FigureOffset(1, -1));

	Figures[2] = Figure(FigureOffset(0, 1), FigureOffset(1, 0), FigureOffset(1, 1));

	Figures[3] = Figure(FigureOffset(-1, 0), FigureOffset(1, 0), FigureOffset(2, 0));
	Figures[4] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(0, 2));

	Figures[5] = Figure(FigureOffset(-1, 1), FigureOffset(0, 1), FigureOffset(1, 0));
	Figures[6] = Figure(FigureOffset(0, -1), FigureOffset(1, 0), FigureOffset(1, 1));

	Figures[7] = Figure(FigureOffset(-1, 0), FigureOffset(-1, -1), FigureOffset(1, 0));
	Figures[8] = Figure(FigureOffset(-1, -1), FigureOffset(0, -1), FigureOffset(0, 1));
	Figures[9] = Figure(FigureOffset(-1, 0), FigureOffset(1, -1), FigureOffset(1, 0));
	Figures[10] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(1, 1));

	Figures[11] = Figure(FigureOffset(-1, 0), FigureOffset(0, 1), FigureOffset(1, 0));
	Figures[12] = Figure(FigureOffset(-1, 0), FigureOffset(0, -1), FigureOffset(0, 1));
	Figures[13] = Figure(FigureOffset(-1, 0), FigureOffset(0, -1), FigureOffset(1, 0));
	Figures[14] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(1, 0));

	Figures[15] = Figure(FigureOffset(-1, 0), FigureOffset(1, 0), FigureOffset(1, 1));
	Figures[16] = Figure(FigureOffset(-1, -1), FigureOffset(0, -1), FigureOffset(0, 1));
	Figures[17] = Figure(FigureOffset(-1, -1), FigureOffset(-1, 0), FigureOffset(1, 0));
	Figures[18] = Figure(FigureOffset(0, -1), FigureOffset(-1, -1), FigureOffset(0, 1));
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
	int glassSizeX = XSize * (ColumnsCount + 2);
	int glassSizeY = YSize * (RowsCount + 1);
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
	DrawFigure(hDC, 0, 0, ColumnsCount / 2, GlassRect);
	InvalidateRect(hWnd, &wndSize, false);
}
void Tetris::DrawFigure(HDC hDC, int idx,  int r, int c, const RECT& glass)
{
	int x = glass.left + XSize + c * XSize;
	int y = glass.top + r * YSize;
	RECT rtCube = {x, y, x + XSize, y + YSize};
	FillRect(hDC, &rtCube, hCube);
	const Figure& figure = Figures[idx];
	for (const FigureOffset& offset : figure.figureOffset)
	{
		int xNew = x + offset.x * XSize;
		int yNew = y + offset.y * YSize;
		RECT rtNewCube = { xNew, yNew, xNew + XSize, yNew + YSize };
		FillRect(hDC, &rtNewCube, hCube);
	}
}