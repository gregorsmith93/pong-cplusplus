#include "paint.h"

// Implementation of painting methods

// Calculate the player rectangle for a given player object within a window
void CalculatePlayerRectangle(RECT window, Player &player, RECT &newPlayerRectangle) {

	// Player current position
	RECT currentPlayerRectangle;

	currentPlayerRectangle.left = player.getPreviousX();
	currentPlayerRectangle.right = player.getPreviousX() + player.getWidth();
	currentPlayerRectangle.top = player.getPreviousY();
	currentPlayerRectangle.bottom = player.getPreviousY() + player.getHeight();

	// Player positon based on potential movement
	RECT calculatedPlayerRectangle;

	calculatedPlayerRectangle.left = window.left + player.getX();
	calculatedPlayerRectangle.right = window.left + player.getX() + player.getWidth();
	calculatedPlayerRectangle.top = window.top + player.getY();
	calculatedPlayerRectangle.bottom = window.top + player.getY() + player.getHeight();

	bool updatePlayerRectangle = false;

	// Player has attempted to move off the bottom of the screen, move them to the buffer distance away from the bottom of the window
	if (calculatedPlayerRectangle.bottom > window.bottom) {
		calculatedPlayerRectangle.bottom = window.bottom - SCREEN_BUFFER;
		calculatedPlayerRectangle.top = calculatedPlayerRectangle.bottom - PLAYER_HEIGHT;
		player.setY(calculatedPlayerRectangle.top);
		updatePlayerRectangle = true;
	}
	// Player has attemped to move off the top of the screen, move them to the buffer distance away from the top of the window
	else if (calculatedPlayerRectangle.top < window.top) {
		player.setY(window.top + SCREEN_BUFFER);
		calculatedPlayerRectangle.top = window.top + SCREEN_BUFFER;
		calculatedPlayerRectangle.bottom = calculatedPlayerRectangle.top + PLAYER_HEIGHT;
		updatePlayerRectangle = true;
	}
	// Players new position is valid
	else if (calculatedPlayerRectangle.bottom < window.bottom && calculatedPlayerRectangle.top > window.top && !EqualRect(&currentPlayerRectangle, &calculatedPlayerRectangle)) {
		updatePlayerRectangle = true;
	}

	// Player should be updated, use calculated position
	if (updatePlayerRectangle) {
		newPlayerRectangle.top = calculatedPlayerRectangle.top;
		newPlayerRectangle.bottom = calculatedPlayerRectangle.bottom;
		newPlayerRectangle.left = calculatedPlayerRectangle.left;
		newPlayerRectangle.right = calculatedPlayerRectangle.right;
	}
	// Player shouldn't be updated, use current position
	else {
		newPlayerRectangle.top = currentPlayerRectangle.top;
		newPlayerRectangle.bottom = currentPlayerRectangle.bottom;
		newPlayerRectangle.left = currentPlayerRectangle.left;
		newPlayerRectangle.right = currentPlayerRectangle.right;
	}
}
   
void UpdatePlayersAndBall(_In_ HWND hwnd, _In_ HDC hdc, _In_ Player &playerOne, _In_ Player &playerTwo, _In_ Ball &ball) {

	RECT rcWindow;
	GetClientRect(hwnd, &rcWindow);

	// Player one current position
	RECT currentPlayerOneRectangle;

	currentPlayerOneRectangle.left = playerOne.getPreviousX();
	currentPlayerOneRectangle.right = playerOne.getPreviousX() + playerOne.getWidth();
	currentPlayerOneRectangle.top = playerOne.getPreviousY();
	currentPlayerOneRectangle.bottom = playerOne.getPreviousY() + playerOne.getHeight();

	// Player two current position
	RECT currentPlayerTwoRectangle;

	currentPlayerTwoRectangle.left = playerTwo.getPreviousX();
	currentPlayerTwoRectangle.right = playerTwo.getPreviousX() + playerTwo.getWidth();
	currentPlayerTwoRectangle.top = playerTwo.getPreviousY();
	currentPlayerTwoRectangle.bottom = playerTwo.getPreviousY() + playerTwo.getHeight();

	// Determine whether or not to update players positions
	RECT newPlayerOne;
	RECT newPlayerTwo;

	CalculatePlayerRectangle(rcWindow, playerOne, newPlayerOne);
	CalculatePlayerRectangle(rcWindow, playerTwo, newPlayerTwo);

	// Ball current position
	RECT currentBallRectangle;

	currentBallRectangle.left = ball.getPreviousX() - BALL_RADIUS;
	currentBallRectangle.right = ball.getPreviousX() + BALL_RADIUS;
	currentBallRectangle.top = ball.getPreviousY() - BALL_RADIUS;
	currentBallRectangle.bottom = ball.getPreviousY() + BALL_RADIUS;

	// Ball new position
	RECT newBallRectangle;

	newBallRectangle.left = ball.getX() - BALL_RADIUS;
	newBallRectangle.right = ball.getX() + BALL_RADIUS;
	newBallRectangle.top = ball.getY() - BALL_RADIUS;
	newBallRectangle.bottom = ball.getY() + BALL_RADIUS;

	SetDCPenColor(hdc, RGB(255, 255, 255));
	InflateRect(&newPlayerOne, -SCREEN_BUFFER, -SCREEN_BUFFER);
	Rectangle(hdc, newPlayerOne.left, newPlayerOne.top, newPlayerOne.right, newPlayerOne.bottom);
	playerOne.MovePlayerYAxis(0);
	InflateRect(&newPlayerTwo, -SCREEN_BUFFER, -SCREEN_BUFFER);
	Rectangle(hdc, newPlayerTwo.left, newPlayerTwo.top, newPlayerTwo.right, newPlayerTwo.bottom);
	playerTwo.MovePlayerYAxis(0);	
	Ellipse(hdc, newBallRectangle.left, newBallRectangle.top, newBallRectangle.right, newBallRectangle.bottom);
	ball.UpdateBallPosition();
}