#pragma once

#include "Chunk.h"

class GameWorld {
public:
    Chunk chunk;  // A single chunk

    GameWorld(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), int size = 16)
        : chunk(position, size) {}  // Create a chunk with specified position and size

    // Render the chunk
    void renderWorld(Mesh& mesh, GLuint programID, glm::mat4 viewProjection) {
        
        chunk.render(mesh, programID, viewProjection);
        
    }
};
