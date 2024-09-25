#pragma once
#include <vector>

#include "GridDefinitions.h"
#include "shader.h"

class SquareRenderer {
public:
	SquareRenderer();

	void init();

	void renderSquare(GridCoord coord);

	void renderSquares(std::vector<GridCoord> coords);
private:
	Shader shader;
	float vertices[];
};