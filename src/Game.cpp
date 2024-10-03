#include "Game.h"
#include "GLFW/glfw3.h"


Game::Game(unsigned int width, unsigned int height, unsigned int length)
    : gameWidth(width)
    , gameHeight(height)
    , startLength(length)
    , widthRandom(0, width-1)
    , heightRandom(0, height-1) {
}

Game::~Game() {
}

void Game::init() {
    grid.clear();
    snakes.clear();

    for (int i = 0; i < gameWidth; ++i) {
        std::vector<GridState> temp = {};
        for (int j = 0; j < gameHeight; ++j) {
            temp.push_back(EMPTY);
        }
        grid.push_back(temp);
    }

    snakes.push_back(Snake(grid, {startLength-1, gameHeight/2}, startLength));

    getNewCherry(snakes);

    currentGameState = GAME_ACTIVE;
}

void Game::processInput(float dt) {
    if (Keys[GLFW_KEY_UP]) {
        if (!snakes.empty()) {
            snakes[0].turnSnake(UP);
        }
        Keys[GLFW_KEY_UP] = false;
    }

    if (Keys[GLFW_KEY_RIGHT]) {
        if (!snakes.empty()) {
            snakes[0].turnSnake(RIGHT);
        }
        Keys[GLFW_KEY_RIGHT] = false;
    }

    if (Keys[GLFW_KEY_DOWN]) {
        if (!snakes.empty()) {
            snakes[0].turnSnake(DOWN);
        }
        Keys[GLFW_KEY_DOWN] = false;
    }

    if (Keys[GLFW_KEY_LEFT]) {
        if (!snakes.empty()) {
            snakes[0].turnSnake(LEFT);
        }
        Keys[GLFW_KEY_LEFT] = false;
    }
}

void Game::update(float dt) {
    timeCounter += dt;
    if (timeCounter >= kStepTime) {
        timeCounter -= kStepTime;
        if (currentGameState == GAME_ACTIVE) {
            stepGame();
        }
    }
}

void Game::stepGame() {
    for (Snake& snake : snakes) {
        snake.planMove();
    }

    bool crashed = false;
    for (Snake& snake : snakes) {
        crashed = (snake.testCrash(snakes) || crashed);
    }

    if (crashed) {
        currentGameState = GAME_OVER;
        return;
    }

    //move snakes forward and empty moved out of spaces
    bool needNewCherry = false;
    std::vector<GridCoord> movedIntoCoords;
    for (Snake& snake : snakes) {
        GridCoord snakeMoveOutSpace = snake.executeMove(snakes);
        if (snakeMoveOutSpace == GridCoord{-1, -1}) { //eaten cherry
            needNewCherry = true;
        } else {
            grid[snakeMoveOutSpace.x][snakeMoveOutSpace.y] = EMPTY;
        }

        movedIntoCoords.push_back(snake.getSnakeHead());

        snake.moveDataReset();
    }

    //then fill moved into spaces (to stop overwriting snakes with empty space)
    for (GridCoord coord : movedIntoCoords) {
        grid[coord.x][coord.y] = SNAKE;
    }

    if (needNewCherry) {
        getNewCherry(snakes);
    }

    //TODO: Sort when got rendering and can see if works...
    //move snakes
    //generate new cherry if necessary
    //get updated squares and update grid
    //render updated squares
}

void Game::render(SquareRenderer& renderer) {
    renderer.renderGrid(grid);
}

bool Game::getNewCherry(std::vector<Snake>& snakes) {

    //gets worse the longers the snake(s) is(are), may need a different method later

    //TODO: also need to check snake isn't filling the screen (otherwise infinite loop...)
    bool collision = false;
    do {
        cherryPos = { widthRandom(mt), heightRandom(mt) };

        for (Snake& snake : snakes) {
            if (collision = snake.checkCollisionWithSelf(cherryPos, false)) { //TODO: Check this works...
                break;
            }
        }
    } while (collision);

    grid[cherryPos.x][cherryPos.y] = CHERRY;

    //mark new cherry pos to be updated/rendered

    return true;
}

//TODO
void Game::reset() {
}
