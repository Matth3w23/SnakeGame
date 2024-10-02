#include "GLFW/glfw3.h"
#include "Game.h"

Game::Game(unsigned int width, unsigned int height, unsigned int length)
    : gameWidth(width)
    , gameHeight(height)
    , startLength(length)
    , widthRandom(1, width)
    , heightRandom(1, height) {
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
        stepGame();
    }
}

void Game::stepGame() {
    for (Snake& snake : snakes) {
        snake.planMove();
    }

    bool crashed = false;
    for (Snake& snake : snakes) {
        crashed = (snake.testMove(snakes) || crashed);
    }

    if (crashed) {
        return;
    }

    //TODO: Sort when got rendering and can see if works...
    //move snakes
    //generate new cherry if necessary
    //get updated squares and update grid
    //render updated squares
}

void Game::renderGame(SquareRenderer& renderer) {
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

    //mark new cherry pos to be updated/rendered

    return true;
}

//TODO
void Game::reset() {
}
