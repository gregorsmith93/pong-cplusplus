#include "ball.h"

Ball::Ball(int t_x, int t_y) {
	m_xPos = t_x;
	m_yPos = t_y;
}

Ball::Ball() {

}

int Ball::getX() {
	return m_xPos;
}

int Ball::getY() {
	return m_yPos;
}