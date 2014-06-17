#include "InputManager.h"

#include "Engine.h"

using namespace std;

InputManager::InputManager()
{

	// Initial position
	position = glm::vec3(0, 0, 0);

	// Initial horizontal angle : toward -Z
	horizontalAngle = 0.0f;

	// Initial vertical angle : none
	verticalAngle = 0.0f;

	// Field of View
	fov = 45.0f;

	speed = 3.0f; // 3 units / second
	mouseSpeed = 1.05f;

	GLFWwindow *window = Engine::getInstance()->getWindow();
	glfwSetCursorPos(window, 1024/2, 768/2);

}

InputManager::~InputManager()
{



}

glm::vec3 InputManager::getDirection()
{

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	return glm::vec3
	(

		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)

	);

}

glm::vec3 InputManager::getRightVector()
{

	return glm::vec3
	(

		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)

	);

}

void InputManager::doComputationsFromInput()
{

	GLFWwindow *window = Engine::getInstance()->getWindow();

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	cout << "xpos: " << xpos << "; ypos: " << ypos << endl;

	// Compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(768/2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction = getDirection();

	// Right vector
	glm::vec3 right = getRightVector();

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

}

glm::mat4 InputManager::getModelMatrix()
{

	return glm::mat4(1.0);

}

glm::mat4 InputManager::getViewMatrix()
{

	glm::vec3 direction = getDirection();

	// Right vector
	glm::vec3 right = getRightVector();

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	return glm::lookAt
	(

		position, // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up // Head is up (set to 0,-1,0 to look upside-down)

	);

}

glm::mat4 InputManager::getProjectionMatrix()
{

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	return glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);

}