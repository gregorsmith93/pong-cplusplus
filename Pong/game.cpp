#include "game.h"

void DetermineNewBallPosition(HWND hwnd, Ball &ball) {

	std::vector<float> directionVector = ball.getDirectionVector();

	int newXPos;
	int newYPos;

	if (directionVector.size() != DIRECTION_VECTOR_CAPACITY) {
		newXPos = ball.getX();
		newYPos = ball.getY();
	}
	else {
		calculateCoordinateFromDirectionVector(directionVector, ball, newXPos, newYPos);

		RECT window;

		GetClientRect(hwnd, &window);

		int ballTopEdge = newYPos - BALL_RADIUS;
		int ballBottomEdge = newYPos + BALL_RADIUS;
		int ballLeftEdge = newXPos - BALL_RADIUS;
		int ballRightEdge = newXPos + BALL_RADIUS;

		if (ballTopEdge <= window.top || ballBottomEdge >= window.bottom) {
			ball.setDirectionVector(directionVector[0], -directionVector[1]);
			calculateCoordinateFromDirectionVector(directionVector, ball, newXPos, newYPos);
		}
	}
	
	ball.moveBall(newXPos, newYPos);
}

void calculateCoordinateFromDirectionVector(std::vector<float> directionVector, Ball ball, int &x, int &y) {

	float xComponent = directionVector[0];
	float yComponent = directionVector[1];
	float angleInRadians = std::atan2(yComponent, xComponent);

	int dx = std::round(BALL_SPEED * std::cos(angleInRadians));
	int dy = std::round(BALL_SPEED * std::sin(angleInRadians));

	x = ball.getX() + dx;
	y = ball.getY() - dy;
}

void DetectPlayerCollision(Ball &ball, Player playerOne, Player playerTwo) {

	int ballTopEdge = ball.getY() - BALL_RADIUS;
	int ballBottomEdge = ball.getY() + BALL_RADIUS;
	int ballLeftEdge = ball.getX() - BALL_RADIUS;
	int ballRightEdge = ball.getX() + BALL_RADIUS;

	int playerOneTopEdge = playerOne.getY();
	int playerOneBottomEdge = playerOne.getY() + PLAYER_HEIGHT;
	int playerOneRightEdge = playerOne.getX() + PLAYER_WIDTH;

	int playerTwoTopEdge = playerTwo.getY();
	int playerTwoBottomEdge = playerTwo.getY() + PLAYER_HEIGHT;
	int playerTwoLeftEdge = playerTwo.getX();

	bool playerOneCollision = false;
	bool playerTwoCollision = false;

	std::vector<float> directionVector = ball.getDirectionVector();

	if (ballLeftEdge <= playerOneRightEdge && ballTopEdge >= playerOneTopEdge && ballBottomEdge <= playerOneBottomEdge) {
		playerOneCollision = true;
	}
	else if (ballRightEdge >= playerTwoLeftEdge && ballTopEdge >= playerTwoTopEdge && ballBottomEdge <= playerTwoBottomEdge) {
		playerTwoCollision = true;
	}

	if (playerOneCollision || playerTwoCollision) {
		ball.setDirectionVector(-directionVector[0], directionVector[1]);
	}
}

OutOfPlayResult DetectBallOutOfPlay(_In_ HWND hwnd, _In_ Ball ball) {

	RECT window;

	GetClientRect(hwnd, &window);

	int ballTopEdge = ball.getY() - BALL_RADIUS;
	int ballBottomEdge = ball.getY() + BALL_RADIUS;
	int ballLeftEdge = ball.getX() - BALL_RADIUS;
	int ballRightEdge = ball.getX() + BALL_RADIUS;

	bool outOfPlay = false;
	unsigned short playerId = 0;

	if (ballLeftEdge <= window.left) {
		outOfPlay = true;
		playerId = 1;
	}

	if (ballRightEdge >= window.right) {
		outOfPlay = true;
		playerId = 2;
	}

	OutOfPlayResult result;
	result.outOfPlay = outOfPlay;
	result.playerId = playerId;

	return result;
}