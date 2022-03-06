#ifndef GAMESTATE_H
#define GAMESTATE_H

/*keeps enum for game states*/

struct GameState {

	enum State {
		IDLE,
		READY,
		ACTIVE,
		LOST,
		WIN
	};
};


#endif 
