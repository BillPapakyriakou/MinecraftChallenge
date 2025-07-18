#include "Window.h"
#include "ShaderLoader.h"
#include "Common.h"
#include "Matrices.h"
#include "Mesh.h"
#include "Camera.h"
#include "Cube.h"
#include "Block.h"
#include "BlockManager.h"
#include "TextureLoader.h"
#include "GameWorld.h"

int main(void) {

	int width, height;

	// Create window
	Window window("Minecraft Challenge", false);

	GLFWwindow* glfwWindow = window.getGLFWwindow();
	glfwGetFramebufferSize(glfwWindow, &width, &height);

	// Set up the matrices
	Matrices matrices;

	Camera camera(&matrices);  // Pass the matrices object to the camera

	// Load texture
	TextureLoader textureLoader;
	GLuint textureID = textureLoader.LoadTextureFromImage("dirt.jpg");



	// Initialize scene
	matrices.initializeScene(width, height);

	// Loads shaders
	GLuint programID = ShaderLoader::LoadShaders("P1BVertexShader.vertexshader", "P1BFragmentShader.fragmentshader");

	// Gets the location of the texture in the shader
	GLuint textureLocation = glGetUniformLocation(programID, "myTextureSampler");
	
	// Use shaders
	glUseProgram(programID);

	// Gets MVP matrix
	GLuint mvpLocation = glGetUniformLocation(programID, "MVP");

	
	// Create the Mesh and BlockManager
	Mesh blockMesh(programID, textureID);   // Mesh handles drawing blocks
	BlockManager blockManager(&blockMesh);  // BlockManager manages blocks

	// Add blocks to the manager
	//blockManager.addBlock(5.0f, 2.0f, 0.0f, 3);  
	

	GameWorld gameWorld;
	gameWorld.generateWorld(25);
	gameWorld.uploadAllChunksToMesh(blockMesh);
	
	//float lastTime = glfwGetTime();

	int lastWidth = width;
	int lastHeight = height;

	do {
		
		/*
		// Calculate deltaTime for frame-rate independent movement
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		*/

		window.clearScreen();

		// Get current framebuffer size
		glfwGetFramebufferSize(glfwWindow, &width, &height);
		glViewport(0, 0, width, height);  // important line, gl magic

		// If size changed, update projection
		if (width != lastWidth || height != lastHeight) {
			float aspect = static_cast<float>(width) / height;
			matrices.setProjectionMatrix(glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f));
			lastWidth = width;
			lastHeight = height;
		}

		// Handle camera movement 
		camera.handleMovement(window.getGLFWwindow());
		

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = matrices.getProjectionMatrix();
		glm::mat4 MVP = projection * view;
		

		gameWorld.renderWorld(blockMesh, programID, MVP);
		

		window.swapBuffers();
		window.pollEvents();

	} while (glfwGetKey(window.getGLFWwindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && !window.shouldClose());

	return 0;

}
