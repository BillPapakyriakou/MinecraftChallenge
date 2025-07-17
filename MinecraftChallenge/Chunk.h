#pragma once

#include "Block.h"
#include "Mesh.h"
#include <vector>
#include "PerlinNoise.hpp"

class Chunk {
public:
    glm::vec3 position;
    int chunkSize;
    std::vector<Block> blocks;

    static siv::PerlinNoise perlin;

    Chunk(glm::vec3 pos, int size = 16);

    void generateChunk();
    void uploadToMesh(Mesh& mesh);  // Upload instance data ONCE
    void render(Mesh& mesh, GLuint programID, glm::mat4 viewProjection);

    const std::vector<Block>& getBlocks() const { return blocks; }
};
