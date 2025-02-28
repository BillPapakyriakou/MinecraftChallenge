#define STB_IMAGE_IMPLEMENTATION  // Define only once

#include "TextureLoader.h"


// Constructor to initialize variables
TextureLoader::TextureLoader()
	: textureID(0), TextureWidth(0), TextureHeight(0), nrChannels(0), imageData(nullptr) {
	glGenTextures(1, &textureID);
}


GLuint TextureLoader::LoadTextureFromImage(const std::string& textureName) {

	// Load the image using stbi_load
	imageData = stbi_load(textureName.c_str(), &TextureWidth, &TextureHeight, &nrChannels, 0);

	if (!imageData) {
		std::cerr << "Failed to load texture!" << std::endl;
		return 0;
	}
	else {
		//std::cout << "Loaded texture!" << std::endl;
	}


	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);


	// Bind texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// clear load image dara
	stbi_image_free(imageData);

	return textureID;

}