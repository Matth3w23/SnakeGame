#include <iostream>
#include <sstream>
#include <fstream>

#include "squareRenderer.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//TODO: Colour
void SquareRenderer::renderSquare(GridCoord coord) {
	shader.Use();

	//always round up to avoid gaps?
	int squareWidth = glm::ceil(static_cast<float>(kWindowWidth) / gameWidth);
	int squareHeight = glm::ceil(static_cast<float>(kWindowHeight) / gameHeight);

	glm::mat4 transform = glm::mat4(1.0f);
	//TODO: make square appropriate size
	transform = glm::scale(transform, glm::vec3(squareWidth, squareHeight, 1.0f));

	shader.SetMatrix4("transform", transform);
	shader.SetVector3f("squareColour", glm::vec3(0.5f, 0.1f, 0.2f));

	glBindVertexArray(squareVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SquareRenderer::renderSquares(std::vector<GridCoord> coords) {
}
