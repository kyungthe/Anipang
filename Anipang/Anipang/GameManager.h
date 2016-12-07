#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <Windows.h>
#include "Bitmap.h"
#include "Character.h"

using namespace std;

class GameManager {
public:
	GameManager();
	~GameManager();
	void update();
	void setInstanceHandle(HINSTANCE instanceHandle);
	void loadBitmap();
	void drawCharacter(HDC hdc);
	void drawBackground(HDC hdc);
	Character* getCharacter(int x, int y);
	void mouseDown(int x, int y);
	void mouseMove(int x, int y);
	void mouseUp();
	void swap();
	void renewalWindow(HWND hWnd);

private:
	Bitmap m_background;
	Character* m_characters[7][7];
	HINSTANCE m_instanceHandle;
	Character* m_clicked;
	Character* m_swap;
	int swapCount;
};

#endif // !_GAMEMANAGER_H
