#pragma once
#include <vector>

#include "GridDefinitions.h"
#include "shader.h"

class SquareRenderer {
public:
	SquareRenderer(int windowWidth, int windowHeight, int gameWidth, int gameHeight);

	void init();

	void renderSquare(GridCoord coord, GridState state = EMPTY);

	void renderGrid(std::vector<std::vector<GridState>>& grid);

	//void renderSquares(std::vector<GridCoord> coords, std::vector<GridState> states);
private:
	unsigned int squareVAO;
	Shader shader;
	//float vertices[];

	const int kWindowWidth;
	const int kWindowHeight;

	int gameWidth;
	int gameHeight;
};