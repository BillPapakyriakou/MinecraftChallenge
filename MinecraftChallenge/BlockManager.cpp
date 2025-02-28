#include "BlockManager.h"

BlockManager::BlockManager(Mesh* mesh) : mesh(mesh) {}

void BlockManager::addBlock(float x, float y, float z, int blockID) {
    blocks.push_back(Block(glm::vec3(x, y, z), blockID));
    updateInstanceBuffer();
}

void BlockManager::removeBlock(float x, float y, float z) {
    auto it = std::find_if(blocks.begin(), blocks.end(),
        [&](const Block& b) { return b.position == glm::vec3(x, y, z); });
    if (it != blocks.end()) {
        blocks.erase(it);  // Remove the block
        updateInstanceBuffer();  // Update the instance buffer
    }
}

void BlockManager::updateInstanceBuffer() {

    std::vector<glm::vec3> positions;
    for (const Block& block : blocks) {
        positions.push_back(block.position);
    }
    mesh->updateInstanceBuffer(positions);  // Update the mesh's buffer
}


const std::vector<Block>& BlockManager::getBlocks() const {
    return blocks;  // Return the list of blocks
}
