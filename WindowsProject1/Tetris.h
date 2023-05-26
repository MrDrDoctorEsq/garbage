#pragma once
#include "GameWindow.h"
#include "bitmap.h"

class Tetris final : public GameWindow
{
private:
	static const int XSize = 20;
	static const int YSize = 20;
	static const int RowsCount = 20;
	static const int ColumnsCount = 30;
	Bitmap background;
	Bitmap glassBackground;
	HBRUSH hBackground;
	HBRUSH hGlassBackground;
	HBRUSH hGlassWall;
public:

	Tetris(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	~Tetris();
	void OnPaint(HDC hDC) override;
};