#pragma once
#include <vector>
#include <queue>

#include "GridDefinitions.h"

/*
//failure of initialising a snake exception
class SnakeInitialisationException : public std::exception {
private:
	char* message;

public:
	SnakeInitialisationException(char* msg) : message(msg) {}
	char* what();
};
*/

//possible results of a snake move
//not sure if needed anymore?
enum SnakeMoveResult {
	MOVED,
	CRASHED,
	CHERRYEATEN
};

class Snake {
public:
	//constructor and destructor
	Snake(std::vector<std::vector<GridState>>& grid, GridCoord startPos = { 3,3 }, int length = 3, GridDirection startDirection = RIGHT); //length >= 3
	~Snake();

	//calculates the moved into place and if snake has eaten a cherry
	void planMove(bool wrapAround = false);

	//check to see if the move will cause a crash
	bool testMove(std::vector<Snake>& snakes);

	//executes planned move
	//returns the coord moved out of or {-1,-1} if eaten a cherry
	//TODO: CHECK IF VECTOR OF SNAKES& would be better
	GridCoord executeMove(std::vector<Snake>& snakes);

	//reset move state
	void moveDataReset();

	//changes snake direction
	//returns true if successfully changed direction, false otherwise
	bool turnSnake(GridDirection turnDirection);

	//checks if gridPosition would collide with snake, including moveToSpace if includeMoveTo = true
	//returns true on collision
	bool checkCollisionWithSelf(GridCoord gridCoord, bool includeMoveTo = true);

	//returns snake head (back of the queue)
	GridCoord getSnakeHead();

private:
	//information about the grid the snake is on
	std::vector<std::vector<GridState>>& grid;
	int gridWidth;
	int gridHeight;

	//snake state
	std::deque<GridCoord> snakeBody;
	GridDirection snakeDirection;

	//state when planning a move
	GridCoord moveToSpace = { -1,-1 };
	bool willEatCherry = false;
};