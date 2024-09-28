#pragma once
#include <vector>

#include "GridDefinitions.h"
#include "shader.h"

class SquareRenderer {
public:
	SquareRenderer(int windowWidth, int windowHeight, int gameWidth, int gameHeight);

	void init();

	void renderSquare(GridCoord coord);

	void renderSquares(std::vector<GridCoord> coords);
private:
	unsigned int squareVAO;
	Shader shader;
	//float vertices[];

	const int kWindowWidth;
	const int kWindowHeight;

	int gameWidth;
	int gameHeight;
};