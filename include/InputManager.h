#pragma once

#include "Singleton.h"

#include "common.h"

using namespace std;

class InputManager : public Singleton<InputManager>
{

	friend class Singleton<InputManager>;

private:

	glm::vec3 position; 
	float horizontalAngle;
	float verticalAngle;
	float fov;
	float speed;
	float mouseSpeed;

	glm::vec3 getDirection();
	glm::vec3 getRightVector();

public:

	InputManager();
	~InputManager();

	void doComputationsFromInput();

	glm::mat4 getModelMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

};