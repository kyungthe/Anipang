#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <Windows.h>

class Bitmap {
public:
	Bitmap();
	~Bitmap();
	Bitmap(const Bitmap& b);
	void draw(HDC hdc, int x, int y);
	int getWidth();
	int getHeight();
	void load(HINSTANCE instanceHandle, int id);
	void load(HINSTANCE instanceHandle, int id, int maskId);
	
private:
	HBITMAP m_bitmap;
	HBITMAP m_bitmapMask;
	int m_width;
	int m_height;
};

#endif // !_BITMAP_H_
