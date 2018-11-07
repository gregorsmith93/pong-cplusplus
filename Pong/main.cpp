#include <Windows.h>
#include <tchar.h>
#include "paint.h"
#include "player.h"

HINSTANCE hInst;
static TCHAR szWindowClass[] = _T("pong");
static TCHAR szTitle[] = _T("Pong C++");

// Game specific variables
Player playerOne;
Player playerTwo;
Ball ball;
bool isGameInitialised = false;

// Forward declaration
LRESULT CALLBACK WndProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

// Main window entry point
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow) {

	// Building window class
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Error"),
			NULL);

		return 1;
	}

	// Create the hwnd object which contains the window
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1200, 800,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Error"),
			NULL);

		return 1;
	}

	// Centering the window
	RECT rc;

	GetWindowRect(hWnd, &rc);

	int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

	SetWindowPos(hWnd, NULL, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Start main message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

}

// Windows event processing handler
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
    // Initial creation message, initialise game state here
	case WM_CREATE: {
		// Calculating variables around window position, and using this initialise the player positions
		RECT clientRectangle;
		GetClientRect(hWnd, &clientRectangle);
		int verticalWindowCenter = clientRectangle.top + ((clientRectangle.bottom - clientRectangle.top) / 2);
		int horizontalWindowCenter = clientRectangle.left + ((clientRectangle.right - clientRectangle.left) / 2);
		playerOne = Player(clientRectangle.left, verticalWindowCenter);
		playerTwo = Player(clientRectangle.right - PLAYER_WIDTH - 5, verticalWindowCenter);
		ball = Ball(horizontalWindowCenter, verticalWindowCenter + (PLAYER_HEIGHT / 2));
		break;
	}
	case WM_PAINT: {
		// If during game initialisation, call the paint intiailising method, otherwise do nothing as paint will be handled without messages
		if (!isGameInitialised) {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			InitialisePlayers(hWnd, hdc, playerOne, playerTwo);
			InitialiseBall(hWnd, hdc, ball);
			EndPaint(hWnd, &ps);
			isGameInitialised = true;
		}
		break; 
	    }
	// Handling all player inputs here
	case WM_KEYDOWN: {
		// Player movement keys
		if (wParam == 0x57) {
			playerOne.MovePlayerYAxis(-1);
		}
		else if (wParam == 0x53) {
			playerOne.MovePlayerYAxis(1);
		}
		else if (wParam == VK_UP) {
			playerTwo.MovePlayerYAxis(-1);
		}
		else if (wParam == VK_DOWN) {
			playerTwo.MovePlayerYAxis(1);
		}

		// Repaint the player positions after movement event
		PaintPlayers(hWnd, playerOne, playerTwo);
		break;
	}
	// Exit message
	case WM_DESTROY: {
		PostQuitMessage(0);
		break; 
	    }
	default: {
		return DefWindowProc(hWnd, message, wParam, lParam);
		break; 
	    }
	}

	return 0;
}
