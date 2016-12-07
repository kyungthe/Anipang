#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <Windows.h>
#include <vector>
#include "Bitmap.h"

using namespace std;

class ResourceManager {
public:
	ResourceManager() {};
	ResourceManager(HINSTANCE hInstance);
	void draw(HDC hdc);

private:
	vector<Bitmap*> m_bitmapList;
};

#endif // !_RESOURCEMANAGER_H_
