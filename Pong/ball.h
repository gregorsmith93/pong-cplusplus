#ifndef BALL_H
#define BALL_H

const int BALL_RADIUS = 15;

class Ball {
    private:
	    int m_xPos, m_yPos;
    public:
	    int getX();
	    int getY();
		Ball(int t_x, int t_y);
		Ball();
};
#endif