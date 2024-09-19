#pragma once
#include<vector>
#include<queue>

#include "GridDefinitions.h"

enum GameState {
	GAME_ACTIVE,
	GAME_OVER
};

class Game {
public:
	// base game state
	bool Keys[1024];
	//constructor and deconstructor
	Game(unsigned int width = 10, unsigned int height = 10, unsigned int length = 3);
	~Game();

	//initialisation
	//	render create snake(s)
	//	render all snakes

	//game loop
	//input
	//update
	//update Game (separate in case paused?)
	// change snake directions
	// move snakes
	// if snakes crashed, stop
	// else move all snakes
	// make new cherry if necessary (can be checked if execute move returns {-1,-1}
	//		spawn cherry randomly, or gather all blanks and spawn using that? Randomly should be expected faster I think?
	//render new squares
private:
	unsigned int gameWidth;
	unsigned int gameHeight;
	unsigned int startLength;

	std::vector<std::vector<GridState>> grid;

	//snake
};