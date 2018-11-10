#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <vector>
#include <math.h>
#include "player.h"
#include "ball.h"

const unsigned int TICK_PERIOD = 5;

struct OutOfPlayResult {
	bool outOfPlay;
	unsigned short playerId;
};

void DetermineNewBallPosition(_In_ HWND hwnd, _In_ Ball &ball);

void calculateCoordinateFromDirectionVector(std::vector<float> directionVector, Ball ball, int &x, int &y);

void DetectPlayerCollision(_In_ Ball &ball, _In_ Player playerOne, _In_ Player playerTwo);

OutOfPlayResult DetectBallOutOfPlay(_In_ HWND hwnd, _In_ Ball ball);

float RandomFloat(float a, float b);

#endif