#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object {
public:
	Object();
	~Object();
	Object(const Object& o);
	void setXY(int x, int y);
	int getX();
	int getY();

protected:
	int m_width;
	int m_height;
	int m_x;
	int m_y;
};

#endif // !_OBJECT_H_
