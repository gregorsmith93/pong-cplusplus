#ifndef BALL_H
#define BALL_H

#include <vector>
#include <math.h>
#include "utils.h"

const int BALL_RADIUS = 12;
const float BALL_SPEED = 15;
const unsigned int DIRECTION_VECTOR_CAPACITY = 2;
const float MAX_BALL_ANGLE = 60;
const double pi = std::atan(1) * 4;

class Ball {
    private:
		// Previous position, used during rendering to determine players current position before attempting to render
		int m_prev_xPos, m_prev_yPos;

		// Ball position after motion
		int m_xPos, m_yPos;

		std::vector<float> m_direction;
    public:
		// Get the previous x position before movement
		int getPreviousX();

		// Get the previous y position before movement
		int getPreviousY();
	    int getX();
	    int getY();
		Ball(int t_x, int t_y);
		Ball();
		void moveBall(int t_x, int t_y);
		void UpdateBallPosition();
		std::vector<float> getDirectionVector();
		void setDirectionVector(float t_x, float t_y);
		void EnsureValidDirectionVector();
		void NormaliseDirectionVector();
};
#endif