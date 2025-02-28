#pragma once

#include "common.h"

class Block {

public:

    glm::vec3 position;  // world position for the block
    int blockID;         // block id (0 = air, 1 = dirt, etc.)


    // Constructor
    Block(glm::vec3 pos, int id) 
        : position(pos),  blockID(id) {}


    // Optionally, add a method to get a string representation of the block's type
    std::string getBlockType() const {
        switch (blockID) {
        case 0: return "Air";
        case 1: return "Dirt";
        case 2: return "Stone";
            // Add other block types as necessary
        default: return "Unknown";
        }
    }

    // Optionally, you could add a method to set the position or block type
    void setPosition(glm::vec3 newPos) {
        position = newPos;
    }

    void setBlockID(int newID) {
        blockID = newID;
    }
    
};