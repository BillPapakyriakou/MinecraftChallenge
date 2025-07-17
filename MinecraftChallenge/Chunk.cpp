#include "Chunk.h"

siv::PerlinNoise Chunk::perlin(12345);  // Seed value 

Chunk::Chunk(glm::vec3 pos, int size)
    : position(pos), chunkSize(size) {
    generateChunk();
}

/*

void Chunk::generateChunkSuperflat() {
    blocks.clear();
    blocks.reserve(chunkSize * chunkSize / 2 * chunkSize);  // Pre-reserve memory for all blocks

    for (int x = 0; x < chunkSize; ++x) {
        //for (int y = 0; y < chunkSize / 2; ++y) {
        for (int y = 0; y < 256; ++y) {
            for (int z = 0; z < chunkSize; ++z) {
                glm::vec3 blockPos = position + glm::vec3(x, y, z);
                int blockID = 1;
                blocks.push_back(Block(blockPos, blockID));
            }
        }
    }
    //std::cout << "Blocks in chunk: " << blocks.size() << std::endl;
}
*/



/*
void Chunk::generateChunk() {
    blocks.clear();

    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            int worldX = static_cast<int>(position.x) + x;
            int worldZ = static_cast<int>(position.z) + z;

            // Large-scale smooth hills
            float largeHill = perlin.noise2D_01(worldX * 0.001f, worldZ * 0.001f);

            // Smaller detail bumps
            float detail = perlin.noise2D_01(worldX * 0.01f, worldZ * 0.01f);

            // Combine them with weights
            float combined = largeHill * 0.7f + detail * 0.3f;

            // Scale to height range (e.g. 50 to 120)
            int height = static_cast<int>(50 + combined * 70);

            if (height > 255) height = 255;

            for (int y = 0; y <= height; ++y) {
                glm::vec3 blockPos = position + glm::vec3(x, y, z);
                int blockID = (y == height) ? 2 : 1; // grass on top, dirt below
                blocks.push_back(Block(blockPos, blockID));
            }
        }
    }
}
*/

void Chunk::generateChunk() {
    blocks.clear();

    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            int worldX = static_cast<int>(position.x) + x;
            int worldZ = static_cast<int>(position.z) + z;

            // Slightly higher frequencies for steeper, more frequent hills
            float largeHill = perlin.noise2D_01(worldX * 0.002f, worldZ * 0.002f);  
            float detail = perlin.noise2D_01(worldX * 0.02f, worldZ * 0.02f);       

            // Adjusted weights to favor detail more for rougher terrain but still mostly smooth
            float combined = largeHill * 0.6f + detail * 0.4f;

            // Increase amplitude a bit for higher hills
            int height = static_cast<int>(50 + combined * 80);  // from 70 to 80 height range

            if (height > 255) height = 255;

            for (int y = 0; y <= height; ++y) {
                glm::vec3 blockPos = position + glm::vec3(x, y, z);
                int blockID = (y == height) ? 2 : 1; // grass on top, dirt below
                blocks.push_back(Block(blockPos, blockID));
            }
        }
    }
}






void Chunk::uploadToMesh(Mesh& mesh) {
    std::vector<glm::vec3> instancePositions;

    if (instancePositions.size() != blocks.size()) {
        instancePositions.clear();
        for (const Block& block : blocks) {
            instancePositions.push_back(block.position);
        }
        mesh.updateInstanceBuffer(instancePositions);  // Upload once when the block data changes
    }
}


void Chunk::render(Mesh& mesh, GLuint programID, glm::mat4 viewProjection) {
    mesh.Render(programID, viewProjection);  // Only render, no updates
}