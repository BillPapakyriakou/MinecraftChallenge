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

	// Create window
	Window window("Minecraft Challenge", false);

	// Set up the matrices
	Matrices matrices;

	Camera camera(&matrices);  // Pass the matrices object to the camera

	// Load texture
	TextureLoader textureLoader;
	GLuint textureID = textureLoader.LoadTextureFromImage("dirt.jpg");


	// Initialize scene
	matrices.initializeScene();

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
	

	// Create a GameWorld with one chunk
	GameWorld gameWorld(glm::vec3(0.0f, 0.0f, 0.0f), 16);

	// Initialize chunk data once
	gameWorld.chunk.uploadToMesh(blockMesh);

	
	//float lastTime = glfwGetTime();

	do {
		
		/*
		// Calculate deltaTime for frame-rate independent movement
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		*/

		window.clearScreen();

		// Handle camera movement 
		camera.handleMovement(window.getGLFWwindow());
		

		// Render the mesh with the current MVP matrix
		glm::mat4 MVP = matrices.getMVP();
		glm::mat4 viewProjection = matrices.getViewProjectionMatrix();

		

		gameWorld.renderWorld(blockMesh, programID, MVP);
		

		window.swapBuffers();
		window.pollEvents();

	} while (glfwGetKey(window.getGLFWwindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && !window.shouldClose());

	return 0;

}
