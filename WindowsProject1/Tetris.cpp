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
	Figures[0] = Figure(FigureOffset(-1, 0), FigureOffset(0, 1), FigureOffset(1, 1), 1, 1);
	Figures[1] = Figure(FigureOffset(0, 1), FigureOffset(1, 0), FigureOffset(1, -1), 0, 0);

	Figures[2] = Figure(FigureOffset(0, 1), FigureOffset(1, 0), FigureOffset(1, 1), 2, 2);

	Figures[3] = Figure(FigureOffset(-1, 0), FigureOffset(1, 0), FigureOffset(2, 0), 4, 4);
	Figures[4] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(0, 2), 3, 3);

	Figures[5] = Figure(FigureOffset(-1, 1), FigureOffset(0, 1), FigureOffset(1, 0), 6, 6);
	Figures[6] = Figure(FigureOffset(0, -1), FigureOffset(1, 0), FigureOffset(1, 1), 5, 5);

	Figures[7] = Figure(FigureOffset(-1, 0), FigureOffset(1, 1), FigureOffset(1, 0), 10, 8);
	Figures[8] = Figure(FigureOffset(-1, 1), FigureOffset(0, -1), FigureOffset(0, 1), 7, 9);
	Figures[9] = Figure(FigureOffset(-1, 0), FigureOffset(-1, -1), FigureOffset(1, 0), 8, 10);
	Figures[10] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(1, -1), 9, 7);

	Figures[11] = Figure(FigureOffset(-1, 0), FigureOffset(0, 1), FigureOffset(1, 0), 14, 12);
	Figures[12] = Figure(FigureOffset(-1, 0), FigureOffset(0, -1), FigureOffset(0, 1), 11, 13);
	Figures[13] = Figure(FigureOffset(-1, 0), FigureOffset(0, -1), FigureOffset(1, 0), 12, 14);
	Figures[14] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(1, 0), 13, 11);

	Figures[15] = Figure(FigureOffset(-1, 0), FigureOffset(1, 0), FigureOffset(1, -1), 18, 16);
	Figures[16] = Figure(FigureOffset(0, -1), FigureOffset(0, 1), FigureOffset(1, 1), 15, 17);
	Figures[17] = Figure(FigureOffset(-1, 0), FigureOffset(-1, 1), FigureOffset(1, 0), 16, 18);
	Figures[18] = Figure(FigureOffset(0, -1), FigureOffset(-1, -1), FigureOffset(0, 1), 17, 15);

	dropTime = 0.1;
	GameOver = false;
	GenerateFigure();
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
	DrawFigure(hDC, currentFigure, currentRow, currentColumn, GlassRect);
	for (int row = 0; row < RowsCount; row++)
	{
		for (int column = 0; column < ColumnsCount; column++)
		{
			if (!Glass[row][column])
			{
				continue;
			}
			int x = GlassRect.left + XSize + column * XSize;
			int y = GlassRect.top + row * YSize;
			RECT rtCube = { x, y, x + XSize, y + YSize };
			FillRect(hDC, &rtCube, hCube);
		}
	}
	if (GameOver)
	{
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor, RGB(0, 0, 0);
		RECT rtText = GlassRect;
		DrawText(hDC, L"Skill Issue", -1, &rtText, DT_CALCRECT);
		RECT rtDrawText = GlassRect;
		rtDrawText.top = (rtDrawText.bottom - rtText.bottom) / 2;
		DrawText(hDC, L"Skill Issue", -1, &rtDrawText, DT_CENTER | DT_VCENTER);
	}
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
void Tetris::OnKeyDown(int vkCode)
{
	if (GameOver)
	{
		return;
	}
	int newRow = currentRow;
	int newColumn = currentColumn;
	int newFigure = currentFigure;
	switch (vkCode)
	{
	case VK_LEFT:
		newColumn--;
		if (newColumn < 0)
		{
			newColumn = 0;
		}
		break;
	case VK_RIGHT:
		newColumn++;
		if (newColumn >= ColumnsCount)
		{
			newColumn = ColumnsCount - 1;
		}
		break;
	case VK_UP:
		newFigure = Figures[currentFigure].next;
			break;
	case VK_SPACE:
		while (!FigureCollide(currentFigure, currentRow, currentColumn))
		{
			currentRow++;
		}
		currentRow--;
		timer = 0;
		return;
	}
	if (newRow == currentRow && newColumn == currentColumn && newFigure == currentFigure)
	{
		return;
	}
	if (FigureCollide(newFigure, newRow, newColumn))
	{
		return;
	}
	currentColumn = newColumn;
	currentRow = newRow;
	currentFigure = newFigure;
}
bool Tetris::FigureCollide(int FigureIdx, int r, int c)
{
	if (Glass[r][c])
	{
		return true;
	}
	const Figure& figure = Figures[FigureIdx];
	for (const FigureOffset& offset : figure.figureOffset)
	{
		int partR = r + offset.y;
		int partC = c + offset.x;
		if (partC < 0 || partC >= ColumnsCount)
		{
			return true;
		}
		if (partR < -1 || partR >= RowsCount)
			return true;
		if (partR < 0)
		{
			continue;
		}
		if (Glass[partR][partC])
		{
			return true;
		}
	}
	return false;
}
void Tetris::Update(float dt)
{
	if (GameOver)
	{
		return;
	}
	timer += dt;
	if (timer < dropTime)
	{
		return;
	}
	timer = 0;
	if (FigureCollide(currentFigure, currentRow + 1, currentColumn))
	{
		SaveFigure(currentFigure, currentRow, currentColumn);
		DropLines();
		GenerateFigure();
		return;
	}
	currentRow++;
}
void Tetris::SaveFigure(int figureIdx, int r, int c)
{
	Glass[r][c] = true;

	const Figure& figure = Figures[figureIdx];
	for (const FigureOffset& offset : figure.figureOffset)
	{
		if (c < 0 || r < 0)
		{
			continue;
		}
		Glass[r + offset.y][c + offset.x] = true;
	}
}
void Tetris::GenerateFigure()
{
	currentRow = 0;
	currentColumn = ColumnsCount / 2;
	currentFigure = rand() % 19;
	timer = 0;
	if (FigureCollide(currentFigure, currentRow, currentColumn))
	{
		GameOver = true;
	}
}
void Tetris::DropLines()
{
	for (int row = 0; row < RowsCount; row++)
	{
		bool needDeleteRow = true;
		for (int column = 0; column < ColumnsCount; column++)
		{
			if (!Glass[row][column])
			{
				needDeleteRow = false;
				break;
			}
		}
		if (needDeleteRow)
		{
			for (int deleteRow = row; deleteRow > 0; deleteRow--)
			{
				for (int column = 0; column < ColumnsCount; column++)
				{
					Glass[deleteRow][column] = Glass[deleteRow - 1][column];
				}
			}
			for (int column = 0; column < ColumnsCount; column++)
			{
				Glass[0][column] = false;
			}
		}
	}
}