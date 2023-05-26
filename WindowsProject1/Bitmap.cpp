#include "Bitmap.h"

Bitmap::Bitmap(const wchar_t* fileName)
{
	hBmp = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBmpDC = CreateCompatibleDC(GetWindowDC(GetDesktopWindow()));

	GetObject(hBmp, sizeof(BITMAP), &bmp);
	SelectObject(hBmpDC, hBmp);
}
Bitmap::~Bitmap()
{
	DeleteObject(hBmp);
	DeleteDC(hBmpDC);
}