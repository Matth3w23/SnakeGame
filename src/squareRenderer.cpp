#include <iostream>
#include <sstream>
#include <fstream>

#include "squareRenderer.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 gridStateToColour(GridState state);

SquareRenderer::SquareRenderer(int windowWidth, int windowHeight, int gameWidth, int gameHeight)
	: kWindowWidth(windowWidth)
	, kWindowHeight(windowHeight)
	, gameWidth(gameWidth)
	, gameHeight(gameHeight) {
	init();
}

void SquareRenderer::init() {

	//read shaders from files
	std::string vertexCodeString, fragmentCodeString;
	std::stringstream vertexStream, fragmentStream;

	std::ifstream vertexShaderFile("Assets/Shaders/squareShader.vert");
	std::ifstream fragmentShaderFile("Assets/Shaders/squareShader.frag");

	vertexStream << vertexShaderFile.rdbuf();
	fragmentStream << fragmentShaderFile.rdbuf();
	vertexShaderFile.close();
	fragmentShaderFile.close();

	vertexCodeString = vertexStream.str();
	fragmentCodeString = fragmentStream.str();

	const char* vertexCode = vertexCodeString.c_str();
	const char* fragmentCode = fragmentCodeString.c_str();
	
	//create and compile shader
	shader = Shader();
	shader.Compile(vertexCode, fragmentCode, nullptr);

	//vertex buffers
	unsigned int VBO;
	unsigned int EBO;
	float vertices[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	unsigned int indices[] = {
		0,2,3,
		0,3,1
	};

	glGenVertexArrays(1, &squareVAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(squareVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//TODO: Colour
void SquareRenderer::renderSquare(GridCoord coord, GridState state) {
	shader.Use();

	//always round up to avoid gaps?
	float squareWidth = 2.0f / gameWidth;
	float squareHeight = 2.0f / gameHeight;

	glm::mat4 transform = glm::mat4(1.0f);
	
	//operations are backwards due to matrix multiplication
	transform = glm::translate(transform, glm::vec3(
		2 * static_cast<float>(coord.x) / gameWidth,
		2 * static_cast<float>(coord.y) / gameHeight,
		0.0f)); //multiplied by 2 as grid is from -1 to 1
	transform = glm::translate(transform, glm::vec3(-1.0f, -1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(squareWidth, squareHeight, 1.0f));

	shader.SetMatrix4("transform", transform);
	shader.SetVector3f("squareColour", gridStateToColour(state));

	glBindVertexArray(squareVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SquareRenderer::renderGrid(std::vector<std::vector<GridState>>& grid) {
	for (int x = 0; x < grid.size(); ++x) {
		for (int y = 0; y < grid[0].size(); ++y) {
			renderSquare({ x,y }, grid[x][y]);
		}
	}
}

/*
void SquareRenderer::renderSquares(std::vector<GridCoord> coords) {
}
*/

glm::vec3 gridStateToColour(GridState state) {
	switch (state) {
	case SNAKE:
		return glm::vec3(23.0f / 255, 46.0f / 255, 255.0f / 255);
	case CHERRY:
		return glm::vec3(255.0f / 255, 23.0f / 255, 31.0f / 255);
	case EMPTY: //should be same as back colour
		return glm::vec3(0, 0, 0);
	default:
		return glm::vec3(255.0f / 255, 23.0f / 255, 247.0f / 255);
	}
}
