#pragma once
#include "GameWindow.h"
#include "bitmap.h"
struct FigureOffset
{
	int x;
	int y;
	FigureOffset():x(0), y(0) {}
	FigureOffset(int x, int y) : x(x), y(y) {}
};
struct Figure
{
	FigureOffset figureOffset[4];
	Figure() {}
		Figure(const FigureOffset& a, const FigureOffset& b, const FigureOffset& c)
	{
		figureOffset[0] = a;
		figureOffset[1] = b;
		figureOffset[2] = c;
	}
};
class Tetris final : public GameWindow
{
private:
	static const int XSize = 20;
	static const int YSize = 20;
	static const int RowsCount = 30;
	static const int ColumnsCount = 20;
	Figure Figures[19];
	Bitmap background;
	Bitmap glassBackground;
	HBRUSH hBackground;
	HBRUSH hGlassBackground;
	HBRUSH hGlassWall;
	HBRUSH hCube;
	void DrawFigure(HDC hDC,int idx, int r, int c, const RECT & glass);
public:

	Tetris(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	~Tetris();
	void OnPaint(HDC hDC) override;
};