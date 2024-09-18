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

	//game loop
	//input
	//update
	//update Game (separate in case paused?)
	//render new squares
private:
	unsigned int gameWidth;
	unsigned int gameHeight;
	unsigned int startLength;

	std::vector<std::vector<GridState>> grid;

	//snake
};