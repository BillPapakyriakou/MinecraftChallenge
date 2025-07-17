#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos, int size)
    : position(pos), chunkSize(size) {
    generateChunk();
}


void Chunk::generateChunk() {
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
    std::cout << "Blocks in chunk: " << blocks.size() << std::endl;
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