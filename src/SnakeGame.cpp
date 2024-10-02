#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "squareRenderer.h"
#include "Game.h"


const int kWindowWidth = 800;
const int kWindowHeight = 600;
const int kGameWidth = 20;
const int kGameHeight = 10;

//callback prototypes

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//TODO
//Game
//GameRenderer

int main() {
	//glfw setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(kWindowWidth, kWindowHeight, "SnakeGame", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, key_callback);


	//load OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//initialise game
	Game game(kGameWidth, kGameHeight);
	game.init();

	//renderer
	SquareRenderer renderer = SquareRenderer(kWindowWidth, kWindowHeight, kGameWidth, kGameHeight);

	float deltaT;
	float lastFrameT = glfwGetTime();

	//main loop
	while (!glfwWindowShouldClose(window)) {
		float curFrameT = glfwGetTime();
		deltaT = curFrameT - lastFrameT;
		lastFrameT = curFrameT;
		
		glfwPollEvents();

		//handle input/update certain grid positions
		game.processInput(deltaT);

		//update game
		game.update(deltaT);
		
		//render grid
		game.render(renderer);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

//callback for adjusting window size
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//key input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//exit on escape
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

