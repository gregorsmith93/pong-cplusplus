#include "paint.h"

// Implementation of painting methods

// Intialise the players for the game
void InitialisePlayers(HWND hwnd, Player playerOne, Player playerTwo) {

	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hwnd, &ps);

	RECT rcWindow;
	GetClientRect(hwnd, &rcWindow);

	// Calculate rectangle for player one
	RECT calculatedPlayerOneRectangle;

	calculatedPlayerOneRectangle.left = rcWindow.left + playerOne.getX();
	calculatedPlayerOneRectangle.right = rcWindow.left + playerOne.getX() + playerOne.getWidth();
	calculatedPlayerOneRectangle.top = rcWindow.top + playerOne.getY();
	calculatedPlayerOneRectangle.bottom = rcWindow.top + playerOne.getY() + playerOne.getHeight();

	// Paint player one rectangle
	InflateRect(&calculatedPlayerOneRectangle, -SCREEN_BUFFER, -SCREEN_BUFFER);
	SetDCPenColor(hdc, RGB(255, 255, 255));
	Rectangle(hdc, calculatedPlayerOneRectangle.left, calculatedPlayerOneRectangle.top, calculatedPlayerOneRectangle.right, calculatedPlayerOneRectangle.bottom);

	// Calculate rectangle for player two
	RECT calculatedPlayerTwoRectangle;

	calculatedPlayerTwoRectangle.left = rcWindow.left + playerTwo.getX();
	calculatedPlayerTwoRectangle.right = rcWindow.left + playerTwo.getX() + playerTwo.getWidth();
	calculatedPlayerTwoRectangle.top = rcWindow.top + playerTwo.getY();
	calculatedPlayerTwoRectangle.bottom = rcWindow.top + playerTwo.getY() + playerTwo.getHeight();

	// Paint player two rectangle
	InflateRect(&calculatedPlayerTwoRectangle, -SCREEN_BUFFER, -SCREEN_BUFFER);
	SetDCPenColor(hdc, RGB(255, 255, 255));
	Rectangle(hdc, calculatedPlayerTwoRectangle.left, calculatedPlayerTwoRectangle.top, calculatedPlayerTwoRectangle.right, calculatedPlayerTwoRectangle.bottom);

	EndPaint(hwnd, &ps);
}

// Paint the players during the game
void PaintPlayers(HWND hwnd, Player playerOne, Player playerTwo) {

	HDC hdc = GetDC(hwnd);

	RECT rcWindow;
	GetClientRect(hwnd, &rcWindow);

	// Player one current position
	RECT currentPlayerOneRectangle;

	currentPlayerOneRectangle.left = playerOne.getPreviousX();
	currentPlayerOneRectangle.right = playerOne.getPreviousX() + playerOne.getWidth();
	currentPlayerOneRectangle.top = playerOne.getPreviousY();
	currentPlayerOneRectangle.bottom = playerOne.getPreviousY() + playerOne.getHeight();

	// Player one positon based on potential movement
	RECT calculatedPlayerOneRectangle;

	calculatedPlayerOneRectangle.left = rcWindow.left + playerOne.getX();
	calculatedPlayerOneRectangle.right = rcWindow.left + playerOne.getX() + playerOne.getWidth();
	calculatedPlayerOneRectangle.top = rcWindow.top + playerOne.getY();
	calculatedPlayerOneRectangle.bottom = rcWindow.top + playerOne.getY() + playerOne.getHeight();

	bool updatePlayerOneRectangle;

	// Player one has attempted to move off the bottom of the screen, move them to the buffer distance away from the bottom of the window
	if (calculatedPlayerOneRectangle.bottom > rcWindow.bottom) {
		calculatedPlayerOneRectangle.bottom = rcWindow.bottom - SCREEN_BUFFER;
		calculatedPlayerOneRectangle.top = calculatedPlayerOneRectangle.bottom - PLAYER_HEIGHT;
		playerOne.setY(calculatedPlayerOneRectangle.top);
		updatePlayerOneRectangle = true;
	}
	// Player one has attemped to move off the top of the screen, move them to the buffer distance away from the top of the window
	else if (calculatedPlayerOneRectangle.top < rcWindow.top) {
		playerOne.setY(rcWindow.top + SCREEN_BUFFER);
		calculatedPlayerOneRectangle.top = rcWindow.top + SCREEN_BUFFER;
		calculatedPlayerOneRectangle.bottom = calculatedPlayerOneRectangle.top + PLAYER_HEIGHT;
		updatePlayerOneRectangle = true;
	} 
	// Player ones new position is valid
	else if (calculatedPlayerOneRectangle.bottom < rcWindow.bottom && calculatedPlayerOneRectangle.top > rcWindow.top) {
		updatePlayerOneRectangle = true;
	}

	// Player two current position
	RECT currentPlayerTwoRectangle;

	currentPlayerTwoRectangle.left = playerTwo.getPreviousX();
	currentPlayerTwoRectangle.right = playerTwo.getPreviousX() + playerTwo.getWidth();
	currentPlayerTwoRectangle.top = playerTwo.getPreviousY();
	currentPlayerTwoRectangle.bottom = playerTwo.getPreviousY() + playerTwo.getHeight();

	// Player one positon based on potential movement
	RECT calculatedPlayerTwoRectangle;

	calculatedPlayerTwoRectangle.left = rcWindow.left + playerTwo.getX();
	calculatedPlayerTwoRectangle.right = rcWindow.left + playerTwo.getX() + playerTwo.getWidth();
	calculatedPlayerTwoRectangle.top = rcWindow.top + playerTwo.getY();
	calculatedPlayerTwoRectangle.bottom = rcWindow.top + playerTwo.getY() + playerTwo.getHeight();

	bool updatePlayerTwoRectangle;

	// Player two has attempted to move off the bottom of the screen, move them to the buffer distance away from the bottom of the window
	if (calculatedPlayerTwoRectangle.bottom > rcWindow.bottom) {
		calculatedPlayerTwoRectangle.bottom = rcWindow.bottom - SCREEN_BUFFER;
		calculatedPlayerTwoRectangle.top = calculatedPlayerTwoRectangle.bottom - PLAYER_HEIGHT;
		playerTwo.setY(calculatedPlayerTwoRectangle.top);
		updatePlayerTwoRectangle = true;
	}
	// Player two has attemped to move off the top of the screen, move them to the buffer distance away from the top of the window
	else if (calculatedPlayerTwoRectangle.top < rcWindow.top) {
		playerTwo.setY(rcWindow.top + SCREEN_BUFFER);
		calculatedPlayerTwoRectangle.top = rcWindow.top + SCREEN_BUFFER;
		calculatedPlayerTwoRectangle.bottom = calculatedPlayerTwoRectangle.top + PLAYER_HEIGHT;
		updatePlayerTwoRectangle = true;
	}
	// Player twos new position is valid
	else if (calculatedPlayerTwoRectangle.bottom < rcWindow.bottom && calculatedPlayerTwoRectangle.top > rcWindow.top) {
		updatePlayerTwoRectangle = true;
	}

	// Determine whether or not to update players positions

	RECT newPlayerOne;
	RECT newPlayerTwo;

	// Player one should be updated, use calculated position
	if (updatePlayerOneRectangle) {
		newPlayerOne.top = calculatedPlayerOneRectangle.top;
		newPlayerOne.bottom = calculatedPlayerOneRectangle.bottom;
		newPlayerOne.left = calculatedPlayerOneRectangle.left;
		newPlayerOne.right = calculatedPlayerOneRectangle.right;
	}
	// Player one shouldn't be updated, use current position
	else {
		newPlayerOne.top = currentPlayerOneRectangle.top;
		newPlayerOne.bottom = currentPlayerOneRectangle.bottom;
		newPlayerOne.left = currentPlayerOneRectangle.left;
		newPlayerOne.right = currentPlayerOneRectangle.right;
	}

	// Player two should be updated, use calculated position
	if (updatePlayerTwoRectangle) {
		newPlayerTwo.top = calculatedPlayerTwoRectangle.top;
		newPlayerTwo.bottom = calculatedPlayerTwoRectangle.bottom;
		newPlayerTwo.left = calculatedPlayerTwoRectangle.left;
		newPlayerTwo.right = calculatedPlayerTwoRectangle.right;
	}
	// Player two shouldn't be updated, use current position
	else {
		newPlayerTwo.top = currentPlayerTwoRectangle.top;
		newPlayerTwo.bottom = currentPlayerTwoRectangle.bottom;
		newPlayerTwo.left = currentPlayerTwoRectangle.left;
		newPlayerTwo.right = currentPlayerTwoRectangle.right;
	}

	// Cleanup current player rectangle
	InvalidateRect(hwnd, &currentPlayerOneRectangle, true);
	InvalidateRect(hwnd, &currentPlayerTwoRectangle, true);
	UpdateWindow(hwnd);

	// Add new rectangles
	InflateRect(&newPlayerOne, -SCREEN_BUFFER, -SCREEN_BUFFER);
	InflateRect(&newPlayerTwo, -SCREEN_BUFFER, -SCREEN_BUFFER);
	SetDCPenColor(hdc, RGB(255, 255, 255));
	Rectangle(hdc, newPlayerOne.left, newPlayerOne.top, newPlayerOne.right, newPlayerOne.bottom);
	Rectangle(hdc, newPlayerTwo.left, newPlayerTwo.top, newPlayerTwo.right, newPlayerTwo.bottom);

	ReleaseDC(hwnd, hdc);
}