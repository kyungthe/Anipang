#include "Character.h"

Character::Character() : m_bitmap() {
	m_width = m_height = m_x = m_y = m_moveX = m_moveY = 0;
}

Character::~Character() {
}

Character::Character(const Character& c) {
	m_bitmap = c.m_bitmap;
	m_type = c.m_type;
	m_moveX = c.m_moveX;
	m_moveY = c.m_moveY;
	m_x = c.m_x;
	m_y = c.m_y;
	m_width = c.m_width;
	m_height = c.m_height;
}

void Character::loadBitmap(HINSTANCE instanceHandle, int id, int maskId) {
	m_bitmap.load(instanceHandle, id, maskId);
}

void Character::draw(HDC hdc) {
	if (m_moveX > 0) m_moveX -= 4;
	else if (m_moveX < 0) m_moveX += 4;
	if (m_moveY > 0) m_moveY -= 4;
	else if (m_moveY < 0) m_moveY += 4;
	
	m_bitmap.draw(hdc, m_x - m_moveX, m_y - m_moveY);
}

void Character::setType(TYPE type) {
	m_type = type;
}

Character::TYPE Character::getType() {
	return m_type;
}

void Character::move(int x, int y) {
	m_moveX = x - m_x;
	m_moveY = y - m_y;
	m_x = x;
	m_y = y;
}

