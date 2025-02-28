#pragma once

#include "Common.h"

class Window {

public:

	int width = 1000;
	int height = 800;

	Window(const std::string& title, bool fullscreen = false);
	~Window();  // destructor: special member function 
				// that is called automatically when an object 
				//of the class goes out of scope or is deleted

	void clearScreen() const;
	void swapBuffers() const;
	void pollEvents() const;
	bool shouldClose() const;
	GLFWwindow* getGLFWwindow() const;

	int getScreenWidth() const { return width; }
	int getScreenHeight() const { return height; }

	glm::mat4 getProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane) const;
	glm::mat4 getViewMatrix(const glm::vec3& cameraPos, const glm::vec3& target, const glm::vec3& up) const;


private:

	GLFWwindow* window;
	void initializeGLFW(int width, int height, const std::string& title, bool fullscreen);
	void initializeGLEW() const;


};

