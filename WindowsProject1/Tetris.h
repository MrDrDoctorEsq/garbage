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
	FigureOffset figureOffset[3];
	int prev;
	int next;
	Figure() {}
		Figure(const FigureOffset& a, const FigureOffset& b, const FigureOffset& c, int p, int n)
	{
		figureOffset[0] = a;
		figureOffset[1] = b;
		figureOffset[2] = c;
		prev = p;
		next = n;
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
	bool Glass[RowsCount][ColumnsCount];
	Bitmap background;
	Bitmap glassBackground;
	HBRUSH hBackground;
	HBRUSH hGlassBackground;
	HBRUSH hGlassWall;
	HBRUSH hCube;
	void DrawFigure(HDC hDC,int idx, int r, int c, const RECT & glass);
	bool FigureCollide(int FigureIdx, int r, int c);
	void SaveFigure(int figureIdx, int r, int c);
	void GenerateFigure();
	void DropLines();
	int currentRow;
	int currentColumn;
	int currentFigure;
	float dropTime;
	float timer;
	bool GameOver;
public:

	Tetris(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	~Tetris();
	void OnPaint(HDC hDC) override;
	void OnKeyDown(int vkCode) override;
	void Update(float dt);
};