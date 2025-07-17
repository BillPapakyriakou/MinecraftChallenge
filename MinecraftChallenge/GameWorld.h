#pragma once

#include "Chunk.h"
#include "Mesh.h"

class GameWorld {
public:
    //Chunk chunk;  // A single chunk
    std::vector<Chunk> chunks; // List of chunks
 

    GameWorld() {}

    void generateWorld(int chunkCount, int chunkSize = 16) {
        chunks.clear();

        for (int i = 0; i < chunkCount; ++i) {
            int x = i % 5;         // lay chunks out in a row of 5 (or adjust layout)
            int z = i / 5;         // increase z every 5 chunks
            glm::vec3 chunkPos = glm::vec3(x * chunkSize, 0, z * chunkSize);

            Chunk chunk(chunkPos, chunkSize);
            chunk.generateChunk();
            chunks.push_back(std::move(chunk));
        }
    }

    void uploadAllChunksToMesh(Mesh& mesh) {
        std::vector<glm::vec3> allPositions;

        for (Chunk& chunk : chunks) {
            for (const Block& block : chunk.getBlocks()) {
                allPositions.push_back(block.position);
            }
        }

        mesh.updateInstanceBuffer(allPositions);

        for (int i = 0; i < chunks.size(); i++) {
            std::cout << "Chunk " << i << " pos: "
                << chunks[i].position.x << ", "
                << chunks[i].position.y << ", "
                << chunks[i].position.z << std::endl;
        }
    }

    void renderWorld(Mesh& mesh, GLuint programID, glm::mat4 viewProjection) {
        mesh.Render(programID, viewProjection);
    }

};
