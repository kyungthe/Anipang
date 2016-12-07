#include "GameManager.h"
#include "resource.h"
#include <cstdlib>
#include <ctime>

GameManager::GameManager() {
	Character::TYPE type;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			m_characters[i][j] = new Character();
			type = static_cast<Character::TYPE>(rand() % 7);
			m_characters[i][j]->setType(type);
			m_characters[i][j]->setXY(52 * j, 138 + 52 * i);
		}
	}

	m_clicked = nullptr;
	m_swap = nullptr;
	swapCount = 0;
}

GameManager::~GameManager() {
}

void GameManager::update() {
}

void GameManager::setInstanceHandle(HINSTANCE instanceHandle) {
	m_instanceHandle = instanceHandle;
}

void GameManager::loadBitmap() {
	Character::TYPE type;

	m_background.load(m_instanceHandle, RESOURCE_BACKGROUND);
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			type = m_characters[i][j]->getType();
			m_characters[i][j]->loadBitmap(m_instanceHandle, RESOURCE_CHARACTER_0 + type, RESOURCE_CHARACTER_0_MASK + type);
		}
	}
}

void GameManager::drawCharacter(HDC hdc) {
	if (swapCount > 0) swapCount -= 4;

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			m_characters[i][j]->draw(hdc);
		}
	}
}

void GameManager::drawBackground(HDC hdc) {
	m_background.draw(hdc, 0, 0);
}

Character* GameManager::getCharacter(int x, int y) {
	if (y - 138 < 0) return nullptr;

	x = x / 52;
	y = (y - 138) / 52;

	if (0 > x || x > 6) return nullptr;
	if (0 > y || y > 6) return nullptr;

	return m_characters[y][x];
}

void GameManager::mouseDown(int x, int y) {
	m_clicked = getCharacter(x, y);
}

void GameManager::mouseMove(int x, int y) {
	if (m_clicked != nullptr) {
		m_swap = getCharacter(x, y);
		if ((swapCount == 0) && (m_clicked != m_swap)) {
			swap();
		}
	}
}

void GameManager::mouseUp() {
	m_clicked = nullptr;
	m_swap = nullptr;
}

void GameManager::swap() {
	int clickedX = m_clicked->getX();
	int clickedY = m_clicked->getY();
	int swapX = m_swap->getX();
	int swapY = m_swap->getY();
	Character* temp = m_characters[(clickedY - 138) / 52][clickedX / 52];

	swapCount = 52;

	m_clicked->move(swapX, swapY);
	m_swap->move(clickedX, clickedY);

	m_characters[(clickedY - 138) / 52][clickedX / 52] = m_characters[(swapY - 138) / 52][swapX / 52];
	m_characters[(swapY - 138) / 52][swapX / 52] = temp;
}

void GameManager::renewalWindow(HWND hWnd) {
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = m_background.getWidth();
	rect.bottom = m_background.getHeight();
	InvalidateRect(hWnd, &rect, true);
}

bool GameManager::isCombo(Character* character) {
	int x = character->getX() / character->getWidth();
	int y = (character->getY() - 138) / character->getHeight();
	int count = 0;

	for (int i = x; i >= 0; --i) {
		if (m_characters[y][i]->getType() == character->getType())
			++count;
		else
			break;
	}
	for (int i = x; i < 7; ++i) {
		if (m_characters[y][i]->getType() == character->getType())
			++count;
		else
			break;
	}
	--count;

	if (count >= 3) {
		character->setCombo(true);
		return true;
	}
	count = 0;

	for (int i = y; i >= 0; --i) {
		if (m_characters[i][x]->getType() == character->getType())
			++count;
		else
			break;
	}
	for (int i = y; i < 7; ++i) {
		if (m_characters[i][x]->getType() == character->getType())
			++count;
		else
			break;
	}
	--count;

	if (count >= 3) {
		character->setCombo(true);
		return true;
	}
	else return false;
}

bool GameManager::searchCombo() {
	bool findCombo = false;

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (isCombo(m_characters[i][j]))
				findCombo = true;
		}
	}

	return findCombo;
}
