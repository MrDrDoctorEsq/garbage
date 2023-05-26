#pragma once
#include "framework.h"

class Bitmap
{
private: 
	BITMAP bmp;
	HBITMAP hBmp;
	HDC hBmpDC;
public:
	HDC GetDC() const { return hBmpDC;  }
	HBITMAP GetHBitmap() const { return hBmp;  }
	const BITMAP& GetBitmap() const { return bmp;  }
	Bitmap(const wchar_t* fileName);
	~Bitmap();
};