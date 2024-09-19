#include <iostream>

#include "Snake.h"

/*
char* SnakeInitialisationException::what() {
	return this->message;
}
*/

Snake::Snake(std::vector<std::vector<GridState>>& grid, GridCoord startPos, unsigned int length, GridDirection startDirection) 
	: grid(grid)
	, snakeDirection(startDirection) {

	//TODO: catch exceptions in main/other

	//check for empty grid
	if (grid.empty() || grid[0].empty()) {
		throw std::exception("Error when initialising Snake: Grid provided to snake is empty.");
	}

	gridWidth = grid.size();
	gridHeight = grid[0].size();

	//boundary check start position
	if (startPos.x < 0 || startPos.x >= gridWidth || startPos.y < 0 || startPos.y >= gridHeight) {
		throw std::exception("Error when initialising Snake: Invalid start position.");
	}

	//check start position is large enough for snake
	//note x >= 0 at this point
	if (startPos.x >= length) {
		throw std::exception("Error when initialising Snake: Start position not large enough for length.");
	}

	//initialise snake
	for (int xPos = startPos.x; xPos > startPos.x - length; --xPos) {
		snakeBody.push_back({ xPos, startPos.y });
	}
}

Snake::~Snake() {
}

void Snake::planMove(bool wrapAround) {
	GridCoord& snakeHead = snakeBody.back();
	switch (snakeDirection) {
	case UP:
		moveToSpace = { snakeHead.x, snakeHead.y + 1 };
		break;
	case RIGHT:
		moveToSpace = { snakeHead.x+1, snakeHead.y };
		break;
	case DOWN:
		moveToSpace = { snakeHead.x, snakeHead.y - 1 };
		break;
	case LEFT:
		moveToSpace = { snakeHead.x-1, snakeHead.y };
		break;
	default:
		std::cout << "Error in snake: move direction not grid direction.";
	}
	if (wrapAround) {
		moveToSpace = { moveToSpace.x % gridWidth, moveToSpace.y % gridHeight };
	}

	if (grid[moveToSpace.x][moveToSpace.y] == CHERRY) {
		willEatCherry = true;
	}
}

bool Snake::testMove(std::vector<Snake>& snakes) {
	//check if offscreen
	if (moveToSpace.x < 0 || moveToSpace.x >= gridWidth || moveToSpace.y < 0 || moveToSpace.y >= gridHeight) {
		return false;
	}
	for (Snake& snake : snakes) {
		if (snake.checkCollisionWithSelf(moveToSpace)) {
			return false;
		}
	}

	return true;

}

GridCoord Snake::executeMove(std::vector<Snake>& snakes) {
	snakeBody.push_back(moveToSpace);
	if (willEatCherry) {
		return { -1,-1 };
	} else {
		GridCoord movedOutOfCoord = { snakeBody.front().x, snakeBody.front().y };
		snakeBody.pop_front();
		return movedOutOfCoord;
	}
}

void Snake::moveDataReset() {
	moveToSpace = { -1,-1 };
	willEatCherry = false;
}

bool Snake::TurnSnake(GridDirection turnDirection) {
	//check snake is not turning directly around
	if (turnDirection == (snakeDirection + 2) % 4) {
		return false;
	}

	snakeDirection = turnDirection;
	return true;
}

bool Snake::checkCollisionWithSelf(GridCoord gridCoord) {
	int cherryModifier = (willEatCherry) ? 0 : -1; //probably could just have will eat cherry as an int

	if ((gridCoord == moveToSpace) || //head on collision
		(!snakeBody.empty() && (find(snakeBody.begin(), snakeBody.end()+cherryModifier, gridCoord)) != snakeBody.end()+cherryModifier)
		) {
		return true;
	} else {
		return false;
	}
}

GridCoord Snake::getSnakeHead() {
	return snakeBody.back();
}

