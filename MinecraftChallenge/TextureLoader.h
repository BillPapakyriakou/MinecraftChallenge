#pragma once


#include "stb_image.h"
#include"Common.h"

class TextureLoader {

public:

	// Create OpenGL texture
	GLuint textureID;
	int TextureWidth, TextureHeight, nrChannels;  // texture data
	unsigned char* imageData;					  // image data for texture

	// Constructor
	TextureLoader();

	GLuint LoadTextureFromImage(const std::string& textureName);

};



