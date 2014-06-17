#pragma once

#include "Singleton.h"

#include "common.h"

class Engine : public Singleton<Engine>
{

	friend class Singleton<Engine>;

private:

	GLFWwindow* window;

	GLuint vertexbuffer;
	GLuint programID;
	GLuint MatrixID;
	GLuint colorbuffer;

public:

	Engine();
	~Engine();

	GLFWwindow *getWindow() { return window; }
	void setWindow(GLFWwindow *window) { this->window = window; }

	bool init();
	void release();

	double calculateFPS(double theTimeInterval, std::string theWindowTitle);

	void run();
	void frame();

};

