#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <Windows.h>
#include "Object.h"
#include "Bitmap.h"

class Character : public Object {
public:
	enum TYPE{ CHICK, DOG, CAT, MONKEY, RAT, RABBIT, PIG };
	Character();
	~Character();
	Character(const Character& c);
	void loadBitmap(HINSTANCE instanceHandle, int id, int maskId);
	void draw(HDC hdc);
	void setType(TYPE type);
	TYPE getType();
	void move(int x, int y);
	void setCombo(bool isCombo);
	bool getCombo();

private:
	Bitmap m_bitmap;
	TYPE m_type;
	int m_moveX;
	int m_moveY;
	bool m_combo;
};

#endif // !_CHARACTER_H_
