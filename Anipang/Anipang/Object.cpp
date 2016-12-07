#include "Object.h"

Object::Object() {
}

Object::~Object() {
}

Object::Object(const Object & o) {
	m_x = o.m_x;
	m_y = o.m_y;
	m_width = o.m_width;
	m_height = o.m_height;
}

void Object::setXY(int x, int y) {
	m_x = x;
	m_y = y;
}

int Object::getX() {
	return m_x;
}

int Object::getY() {
	return m_y;
}

int Object::getWidth() {
	return m_width;
}

int Object::getHeight() {
	return m_height;
}
