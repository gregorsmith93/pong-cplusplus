#include "ball.h"

Ball::Ball(int t_x, int t_y) {
	m_prev_xPos = t_x;
	m_prev_yPos = t_y;
	m_xPos = t_x;
	m_yPos = t_y;
}

Ball::Ball() {

}

// Get the previous x position before movement
int Ball::getPreviousX() {
	return m_prev_xPos;
}

// Get the previous y position before movement
int Ball::getPreviousY() {
	return m_prev_yPos;
}

int Ball::getX() {
	return m_xPos;
}

int Ball::getY() {
	return m_yPos;
}

void Ball::moveBall(int t_x, int t_y) {
	m_prev_xPos = m_xPos;
	m_prev_yPos = m_yPos;
	m_xPos = t_x;
	m_yPos = t_y;
}

void Ball::UpdateBallPosition() {
	m_prev_xPos = m_xPos;
	m_prev_yPos = m_yPos;
}

std::vector<float> Ball::getDirectionVector() {
	return m_direction;
}

void Ball::setDirectionVector(float t_x, float t_y) {
	m_direction = { t_x, t_y };
	EnsureValidDirectionVector();
	NormaliseDirectionVector();
}

void Ball::EnsureValidDirectionVector() {
	float xComponent = m_direction[0];
	float yComponent = m_direction[1];
	float angleInRadians = std::atan2(yComponent, xComponent);
	float angleInDegrees = angleInRadians * (180 / pi);

	bool invalidDirectionVector = false;

	if (angleInDegrees >= 0 && angleInDegrees > MAX_BALL_ANGLE && (180 - MAX_BALL_ANGLE) > angleInDegrees ) {
		invalidDirectionVector = true;
	}
	else if (angleInDegrees < 0 && angleInDegrees < (-MAX_BALL_ANGLE) && -(180 - MAX_BALL_ANGLE) < angleInDegrees) {
		invalidDirectionVector = true;
	}

	if (invalidDirectionVector) {
		float maxBallAngleInRadians = MAX_BALL_ANGLE * (pi / 180);
		float ensuredXComponent = BALL_SPEED * std::cos(maxBallAngleInRadians);
		float ensuredYComponent = BALL_SPEED * std::sin(maxBallAngleInRadians);

		if (xComponent < 0) {
			ensuredXComponent *= -1;
		}

		if (yComponent < 0) {
			ensuredYComponent *= -1;
		}

		m_direction = { ensuredXComponent, ensuredYComponent };
	}
}

void Ball::NormaliseDirectionVector() {
	float length = sqrt(m_direction[0] * m_direction[0] + m_direction[1] * m_direction[1]);

	if (length != 0) {
		m_direction[0] = m_direction[0] / length;
		m_direction[1] = m_direction[1] / length;
	}
}