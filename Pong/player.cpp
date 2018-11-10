#include "player.h"

// Implementations for the Player class

// Constructor which defines initial position, sets width and height to default defined in header
Player::Player(int t_x, int t_y) {
	m_prev_xPos = t_x;
	m_prev_yPos = t_y;
	m_xPos = t_x;
	m_yPos = t_y;
	m_width = PLAYER_WIDTH;
	m_height = PLAYER_HEIGHT;
	m_score = 0;
}

// Default constructor
Player::Player() {

}

// Get x axis position after movement has been applied
int Player::getX() {
	return m_xPos;
}

// Get y axis position after movement has been applied
int Player::getY() {
	return m_yPos;
}

// Set the y axis position, only used when player hits the window boundaries in order to manually set them to the edge
void Player::setY(int t_y) {
	m_prev_yPos = t_y;
	m_yPos = t_y;
}

// Get the previous x position before movement
int Player::getPreviousX() {
	return m_prev_xPos;
}

// Get the previous y position before movement
int Player::getPreviousY() {
	return m_prev_yPos;
}

// Get player width, this should usually equal PLAYER_WIDTH defined above, but go through here in case this ever becomes configurable
int Player::getHeight() {
	return m_height;
}

// Get player height, this should usually equal PLAYER_HEIGHT defined above, but go through here in case this ever becomes configurable
int Player::getWidth() {
	return m_width;
}

// Move a player along the y axis. Positive value for input parameter will increase y axis value moving the player down the screen, and vice versa.
// Movement will only ever be in increments of the constant PLAYER_SPEED.
void Player::MovePlayerYAxis(int t_direction) {
	m_prev_yPos = m_yPos;
	if (t_direction > 0) {
		m_prev_yPos = m_yPos;
		m_yPos += PLAYER_SPEED;
	}
	else if (t_direction < 0) {
		m_prev_yPos = m_yPos;
		m_yPos -= PLAYER_SPEED;
	}
}

int Player::getScore() {
	return m_score;
}

void Player::setScore(int t_x) {
	m_score = t_x;
}

void Player::incrementScore() {
	m_score += 1;
}