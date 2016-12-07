#include "Bitmap.h"

Bitmap::Bitmap() {
	m_bitmap = m_bitmapMask = NULL;
	m_width = m_height = 0;
}

Bitmap::~Bitmap() {
	if (m_bitmap != NULL) DeleteObject(m_bitmap);
	if (m_bitmapMask != NULL) DeleteObject(m_bitmapMask);
}

Bitmap::Bitmap(const Bitmap & b) {
	if (m_bitmap != NULL) DeleteObject(m_bitmap);
	if (m_bitmapMask != NULL) DeleteObject(m_bitmapMask);

	m_bitmap = b.m_bitmap;
	m_bitmapMask = b.m_bitmapMask;
	m_width = b.m_width;
	m_height = b.m_height;
}

void Bitmap::draw(HDC hdc, int x, int y) {
	HDC MemDC;
	HBITMAP OldBitmap;

	if (m_bitmap != NULL) {
		MemDC = CreateCompatibleDC(hdc);
		// 비트맵 마스크가 있으면
		if (m_bitmapMask != NULL) {
			OldBitmap = (HBITMAP)SelectObject(MemDC, m_bitmapMask);
			BitBlt(hdc, x, y, m_width, m_height, MemDC, 0, 0, SRCAND);
			OldBitmap = (HBITMAP)SelectObject(MemDC, m_bitmap);
			BitBlt(hdc, x, y, m_width, m_height, MemDC, 0, 0, SRCINVERT);
		}
		// 비트맵 마스크가 없으면
		else {
			OldBitmap = (HBITMAP)SelectObject(MemDC, m_bitmap);
			BitBlt(hdc, x, y, m_width, m_height, MemDC, 0, 0, SRCCOPY);
		}
		SelectObject(MemDC, OldBitmap);
		DeleteDC(MemDC);
	}
}

int Bitmap::getWidth() {
	return m_width;
}

int Bitmap::getHeight() {
	return m_height;
}

void Bitmap::load(HINSTANCE instanceHandle, int id) {
	if (m_bitmap != NULL) DeleteObject(m_bitmap);

	m_bitmap = LoadBitmap(instanceHandle, MAKEINTRESOURCE(id));
	m_bitmapMask = NULL;

	BITMAP bitmap;
	GetObject(m_bitmap, sizeof(BITMAP), &bitmap);

	m_width = bitmap.bmWidth;
	m_height = bitmap.bmHeight;
}

void Bitmap::load(HINSTANCE instanceHandle, int id, int maskId) {
	if (m_bitmap != NULL) DeleteObject(m_bitmap);
	if (m_bitmapMask != NULL) DeleteObject(m_bitmapMask);

	m_bitmap = LoadBitmap(instanceHandle, MAKEINTRESOURCE(id));
	m_bitmapMask = LoadBitmap(instanceHandle, MAKEINTRESOURCE(maskId));

	BITMAP bitmap;
	GetObject(m_bitmap, sizeof(BITMAP), &bitmap);

	m_width = bitmap.bmWidth;
	m_height = bitmap.bmHeight;
}
