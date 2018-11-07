#ifndef PAINT_H
#define PAINT_H

#include <Windows.h>
#include "player.h"
#include "ball.h"

// Provides methods for painting the game

// Constants
const int SCREEN_BUFFER = 5;

// Intialise the players for the game
void InitialisePlayers(_In_ HWND hwnd, _In_ HDC hdc,_In_ Player playerOne, _In_ Player playerTwo);

// Initialise the ball for the game
void InitialiseBall(_In_ HWND hwnd, _In_ HDC hdc, _In_ Ball ball);

// Paint the players during the game
void PaintPlayers(_In_ HWND hwnd, _In_ Player playerOne, _In_ Player playerTwo);

// Calculate the player rectangle for a given player object within a window
void CalculatePlayerRectangle(_In_ RECT window, _In_ Player player, _In_ RECT &newPlayerRectangle);
#endif