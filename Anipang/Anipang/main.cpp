#include <Windows.h>
#include "GameManager.h"
#include "ResourceManager.h"

#define FPS		60

GameManager* gameManager = nullptr;
int startTick = GetTickCount();
int delay;
int interval = 1000 / FPS;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		gameManager->mouseDown(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_MOUSEMOVE:
		gameManager->mouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONUP:
		gameManager->mouseUp();
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		gameManager->drawBackground(hdc);
		gameManager->drawCharacter(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASS wc;

	gameManager = new GameManager();
	gameManager->setInstanceHandle(hInstance);
	gameManager->loadBitmap();
	
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Anipang";
	wc.lpszMenuName = NULL;
	wc.style = NULL;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(wc.lpszClassName, L"Anipang", WS_OVERLAPPEDWINDOW, 100, 90, 380, 650, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	bool play = true;

	while (play) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				play = false;
			} 
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		delay = interval - (GetTickCount() - startTick);
		if (delay < 0) {
			gameManager->renewalWindow(hWnd);
			startTick = GetTickCount();
		}
	}

	return msg.wParam;
}