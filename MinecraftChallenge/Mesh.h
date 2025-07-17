#pragma once

#include "Common.h"
#include "PerlinNoise.hpp"

class Mesh {

private:

    GLuint VAO, VBO[3], EBO;    // one VAO multiple VBOs
    GLuint instanceVBO;         // stores block positions
    GLuint programID;
    GLuint textureID;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    std::vector<GLuint> indices;
    std::vector<GLfloat> uvs;

    std::vector<glm::vec3> m_instancePositions;  // Store block positions (for instancing)
   


public:

    
    Mesh(GLuint programID, GLuint textureID);

    ~Mesh();

    void setupMesh();


    void updateInstanceBuffer(const std::vector<glm::vec3>& instanceData);

    void Render(GLuint programID, glm::mat4 viewProjection);


};
