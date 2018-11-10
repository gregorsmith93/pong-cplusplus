#ifndef PLAYER_H
#define PLAYER_H

// Player constants
const int PLAYER_HEIGHT = 120;
const int PLAYER_WIDTH = 30;
const int PLAYER_SPEED = 200  ;

// Holds information relating to an individual player, i.e. position.
class Player {
	// Private members
    private:
		// Previous position, used during rendering to determine players current position before attempting to render
		int m_prev_xPos, m_prev_yPos;

		// Players position after motion
	    int m_xPos,m_yPos;

		// Player physical properties
	    int m_width, m_height;

		int m_score;
    // Public methods
    public:
		// Get x axis position after movement has been applied
	    int getX();

		// Get y axis position after movement has been applied
		int getY();

		// Set the y axis position, only used when player hits the window boundaries in order to manually set them to the edge
		void setY(int t_y);

		// Get the previous x position before movement
		int getPreviousX();

		// Get the previous y position before movement
		int getPreviousY();

		// Get player width, this should usually equal PLAYER_WIDTH defined above, but go through here in case this ever becomes configurable
		int getWidth();

		// Get player height, this should usually equal PLAYER_HEIGHT defined above, but go through here in case this ever becomes configurable
		int getHeight();

		// Constructor which defines initial position
		Player(int t_x, int t_y);

		// Default constructor
		Player();

		// Move a player along the y axis
		void MovePlayerYAxis(int t_direction);

		int getScore();

		void setScore(int t_x);

		void incrementScore();
};
#endif
