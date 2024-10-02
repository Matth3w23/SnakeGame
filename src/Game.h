#pragma once
#include<vector>
#include<queue>
#include <random>

#include "GridDefinitions.h"
#include "Snake.h"

//not used yet
enum GameState {
	GAME_ACTIVE,
	GAME_OVER
};

class Game {
public:
	// base game state
	bool Keys[1024] = { false };
	//constructor and deconstructor
	Game(unsigned int width = 10, unsigned int height = 10, unsigned int length = 3);
	~Game();


	void init();
	//initialisation
	// empty grid
	// refill grid
	// destroy snakes?
	//	create snake(s)
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
	// render new squares

	void processInput(float dt);
	//increment counter, call step game when needed?
	void update(float dt);
	//move all snakes
	void stepGame();

	bool getNewCherry(std::vector<Snake>& snakes);

	//reset game
	void reset();
private:
	float timeCounter = 0.0;
	const float kStepTime = 0.5;

	int gameWidth;
	int gameHeight;
	int startLength;

	std::vector<std::vector<GridState>> grid;
	std::vector<std::pair<GridCoord, GridState>> gridUpdates;
	GridCoord cherryPos;

	std::vector<Snake> snakes;

	//random number stuff
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };
	std::uniform_int_distribution<> widthRandom;
	std::uniform_int_distribution<> heightRandom;
};