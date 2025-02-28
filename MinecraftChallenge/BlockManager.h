#pragma once

#include "Block.h"
#include "Mesh.h"

class BlockManager {
private:
    std::vector<Block> blocks;  // Store blocks with positions and types
    Mesh* mesh;  // Pointer to the Mesh object that will render the blocks

public:
    // Constructor that accepts a pointer to a Mesh object for rendering
    BlockManager(Mesh* mesh);

    // Add a new block at a specific position with a given block ID
    void addBlock(float x, float y, float z, int blockID);

    // Remove a block by its position
    void removeBlock(float x, float y, float z);

    // Update the instance buffer with the current block positions
    void updateInstanceBuffer();

    // Get the blocks (for debugging or further use)
    const std::vector<Block>& getBlocks() const;
};

