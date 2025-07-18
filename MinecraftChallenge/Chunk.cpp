#include "Chunk.h"

siv::PerlinNoise Chunk::perlin(12345);  // Seed value 

Chunk::Chunk(glm::vec3 pos, int size)
    : position(pos), chunkSize(size) {
    generateChunk();
}



/*
void Chunk::generateChunkSuperflat() {
    blocks.clear();

    constexpr int height = 256;
    bool solid[16][height][16] = {};

    // Fill the solid array (superflat solid blocks up to height)
    for (int x = 0; x < chunkSize; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < chunkSize; ++z) {
                solid[x][y][z] = true;
            }
        }
    }

    // Reserve max possible visible blocks (very rough guess)
    blocks.reserve(chunkSize * height * chunkSize / 2);

    // Add only visible blocks (blocks with at least one empty neighbor)
    for (int x = 0; x < chunkSize; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < chunkSize; ++z) {
                // Check if block is solid (always true here)
                if (!solid[x][y][z]) continue;

                bool visible = false;

                if (x == 0 || !solid[x - 1][y][z]) visible = true;
                else if (x == chunkSize - 1 || !solid[x + 1][y][z]) visible = true;
                else if (y == 0 || !solid[x][y - 1][z]) visible = true;
                else if (y == height - 1 || !solid[x][y + 1][z]) visible = true;
                else if (z == 0 || !solid[x][y][z - 1]) visible = true;
                else if (z == chunkSize - 1 || !solid[x][y][z + 1]) visible = true;

                if (visible) {
                    glm::vec3 blockPos = position + glm::vec3(x, y, z);
                    int blockID = (y == height - 1) ? 2 : 1;  // grass on top layer, dirt otherwise
                    blocks.push_back(Block(blockPos, blockID));
                }
            }
        }
    }
}
*/

/*
// Without caves (2D perlin noise) ver1
void Chunk::generateChunk() {
    blocks.clear();

    // Track solid blocks in the chunk for face culling
    bool solid[16][256][16] = {};

    // First pass: generate terrain height and fill solid array
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            int worldX = static_cast<int>(position.x) + x;
            int worldZ = static_cast<int>(position.z) + z;

            // Your noise values
            float largeHill = perlin.noise2D_01(worldX * 0.001f, worldZ * 0.001f);
            float detail = perlin.noise2D_01(worldX * 0.01f, worldZ * 0.01f);
            float combined = largeHill * 0.7f + detail * 0.3f;

            int height = static_cast<int>(50 + combined * 70);
            if (height > 255) height = 255;

            for (int y = 0; y <= height; ++y) {
                solid[x][y][z] = true;
            }
        }
    }

    // Second pass: add only blocks that have at least one empty neighbor (visible blocks)
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            for (int y = 0; y < 256; ++y) {
                if (!solid[x][y][z]) continue;

                bool visible = false;

                if (x == 0 || !solid[x - 1][y][z]) visible = true;
                else if (x == chunkSize - 1 || !solid[x + 1][y][z]) visible = true;
                else if (y == 0 || !solid[x][y - 1][z]) visible = true;
                else if (y == 255 || !solid[x][y + 1][z]) visible = true;
                else if (z == 0 || !solid[x][y][z - 1]) visible = true;
                else if (z == chunkSize - 1 || !solid[x][y][z + 1]) visible = true;

                if (visible) {
                    glm::vec3 blockPos = position + glm::vec3(x, y, z);
                    int blockID = (y == 255 || !solid[x][y + 1][z]) ? 2 : 1; // grass on top if topmost visible block
                    blocks.push_back(Block(blockPos, blockID));
                }
            }
        }
    }
}
*/


/*
// Without caves (2D perlin noise) ver2
void Chunk::generateChunk() {
    blocks.clear();

    // Temporary array to track solid blocks
    bool solid[16][256][16] = {};

    // === First pass: Fill solid blocks based on 2D terrain ===
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            int worldX = static_cast<int>(position.x) + x;
            int worldZ = static_cast<int>(position.z) + z;

            float largeHill = perlin.noise2D_01(worldX * 0.002f, worldZ * 0.002f);
            float detail = perlin.noise2D_01(worldX * 0.02f, worldZ * 0.02f);

            float combined = largeHill * 0.6f + detail * 0.4f;
            int height = static_cast<int>(50 + combined * 80);
            if (height > 255) height = 255;

            for (int y = 0; y <= height; ++y) {
                solid[x][y][z] = true; // mark as filled
            }
        }
    }

    // === Second pass: Add only visible blocks (those with at least one exposed face) ===
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            for (int y = 0; y < 256; ++y) {
                if (!solid[x][y][z]) continue;

                bool visible = false;

                // Check 6 neighbor directions
                if (x == 0 || !solid[x - 1][y][z]) visible = true;
                else if (x == chunkSize - 1 || !solid[x + 1][y][z]) visible = true;
                else if (y == 0 || !solid[x][y - 1][z]) visible = true;
                else if (y == 255 || !solid[x][y + 1][z]) visible = true;
                else if (z == 0 || !solid[x][y][z - 1]) visible = true;
                else if (z == chunkSize - 1 || !solid[x][y][z + 1]) visible = true;

                if (visible) {
                    glm::vec3 blockPos = position + glm::vec3(x, y, z);
                    int blockID = (y + 1 >= 256 || !solid[x][y + 1][z]) ? 2 : 1; // grass on top
                    blocks.push_back(Block(blockPos, blockID));
                }
            }
        }
    }
}
*/


/*
// With caves (3D perlin noise) ver1
void Chunk::generateChunk() {
    blocks.clear();

    constexpr int maxHeight = 256;
    bool solid[16][maxHeight][16] = {};

    // Step 1: Generate solid blocks with caves
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            int worldX = static_cast<int>(position.x) + x;
            int worldZ = static_cast<int>(position.z) + z;

            // Surface height with 2D noise
            float heightNoise = perlin.noise2D_01(worldX * 0.002f, worldZ * 0.002f);
            int surfaceHeight = static_cast<int>(50 + heightNoise * 80);
            if (surfaceHeight > maxHeight - 1) surfaceHeight = maxHeight - 1;

            for (int y = 0; y <= surfaceHeight; ++y) {
                // 3D noise for caves
                float caveNoise = perlin.noise3D_01(worldX * 0.05f, y * 0.05f, worldZ * 0.05f);

                // If caveNoise < threshold, it's air (no block)
                if (caveNoise < 0.45f) {
                    solid[x][y][z] = false;
                }
                else {
                    solid[x][y][z] = true;
                }
            }

            // Above surface, everything is air
            for (int y = surfaceHeight + 1; y < maxHeight; ++y) {
                solid[x][y][z] = false;
            }
        }
    }

    // Step 2: Add only visible blocks (blocks with at least one air neighbor)
    for (int x = 0; x < chunkSize; ++x) {
        for (int y = 0; y < maxHeight; ++y) {
            for (int z = 0; z < chunkSize; ++z) {
                if (!solid[x][y][z]) continue;

                bool visible = false;

                // Check neighbors (with bounds checks)
                if (x == 0 || !solid[x - 1][y][z]) visible = true;
                else if (x == chunkSize - 1 || !solid[x + 1][y][z]) visible = true;
                else if (y == 0 || !solid[x][y - 1][z]) visible = true;
                else if (y == maxHeight - 1 || !solid[x][y + 1][z]) visible = true;
                else if (z == 0 || !solid[x][y][z - 1]) visible = true;
                else if (z == chunkSize - 1 || !solid[x][y][z + 1]) visible = true;

                if (visible) {
                    glm::vec3 blockPos = position + glm::vec3(x, y, z);
                    int blockID = 1;  // dirt block ID, can customize if you want
                    blocks.push_back(Block(blockPos, blockID));
                }
            }
        }
    }
}
*/


// With caves (3D perlin noise) ver2
void Chunk::generateChunk() {
    blocks.clear();

    constexpr int maxHeight = 256;
    bool solid[16][maxHeight][16] = {};

    // Step 1: Generate solid blocks with caves
    for (int x = 0; x < chunkSize; ++x) {
        for (int z = 0; z < chunkSize; ++z) {
            int worldX = static_cast<int>(position.x) + x;
            int worldZ = static_cast<int>(position.z) + z;

            float heightNoise = perlin.noise2D_01(worldX * 0.0025f, worldZ * 0.0025f);
            int surfaceHeight = static_cast<int>(50 + heightNoise * 80);
            if (surfaceHeight > maxHeight - 1) surfaceHeight = maxHeight - 1;

            for (int y = 0; y <= surfaceHeight; ++y) {
                float caveNoise = perlin.noise3D_01(worldX * 0.055f, y * 0.055f, worldZ * 0.055f);

                if (caveNoise < 0.42f) {
                    solid[x][y][z] = false; // cave (air)
                }
                else {
                    solid[x][y][z] = true; // solid block
                }
            }
            // Above surface is air
            for (int y = surfaceHeight + 1; y < maxHeight; ++y) {
                solid[x][y][z] = false;
            }
        }
    }

    // Step 2: Add only visible blocks (blocks with at least one air neighbor)
    for (int x = 0; x < chunkSize; ++x) {
        for (int y = 0; y < maxHeight; ++y) {
            for (int z = 0; z < chunkSize; ++z) {
                if (!solid[x][y][z]) continue;

                bool visible = false;

                if (x == 0 || !solid[x - 1][y][z]) visible = true;
                else if (x == chunkSize - 1 || !solid[x + 1][y][z]) visible = true;
                else if (y == 0 || !solid[x][y - 1][z]) visible = true;
                else if (y == maxHeight - 1 || !solid[x][y + 1][z]) visible = true;
                else if (z == 0 || !solid[x][y][z - 1]) visible = true;
                else if (z == chunkSize - 1 || !solid[x][y][z + 1]) visible = true;

                if (visible) {
                    glm::vec3 blockPos = position + glm::vec3(x, y, z);
                    int blockID = 1;  // dirt block
                    blocks.push_back(Block(blockPos, blockID));
                }
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