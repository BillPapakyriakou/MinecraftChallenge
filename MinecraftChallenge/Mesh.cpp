#include "Mesh.h"



Mesh::Mesh(GLuint programID, GLuint textureID)
    : programID(programID), textureID(textureID) {
    setupMesh();

}


Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(3, VBO);  // Cleanup VBOs
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &instanceVBO);
}



void Mesh::setupMesh() {


    std::vector<GLfloat> vertices = {

        // Back
           1.0f, 0.0f, 0.0f,    // bottom-left
           0.0f, 0.0f, 0.0f,    // bottom-right
           0.0f, 1.0f, 0.0f,    // top-right
           1.0f, 1.0f, 0.0f,    // top-left

           // Front
           0.0f, 0.0f, 1.0f,    // bottom-left
           1.0f, 0.0f, 1.0f,    // bottom-right
           1.0f, 1.0f, 1.0f,    // top-right
           0.0f, 1.0f, 1.0f,    // top-left

           // Right face (corrected)
           1.0f, 0.0f, 0.0f,    // bottom-left
           1.0f, 0.0f, 1.0f,    // bottom-right
           1.0f, 1.0f, 1.0f,    // top-right
           1.0f, 1.0f, 0.0f,    // top-left

           // Left face
           0.0f, 0.0f, 0.0f,    // bottom-left
           0.0f, 0.0f, 1.0f,    // bottom-right
           0.0f, 1.0f, 1.0f,    // top-right
           0.0f, 1.0f, 0.0f,    // top-left

           // Top face
           0.0f, 1.0f, 1.0f,    // bottom-left
           1.0f, 1.0f, 1.0f,    // bottom-right
           1.0f, 1.0f, 0.0f,    // top-right
           0.0f, 1.0f, 0.0f,    // top-left

           // Bottom face
           0.0f, 0.0f, 0.0f,    // bottom-left
           1.0f, 0.0f, 0.0f,    // bottom-right
           1.0f, 0.0f, 1.0f,    // top-right
           0.0f, 0.0f, 1.0f     // top-left

    };


    indices = {
            
            // Back face
            0, 1, 2, 2, 3, 0,

            // Front face
            4, 5, 6, 6, 7, 4,

            // Right face
            8, 9, 10, 10, 11, 8,

            // Left face
            12, 13, 14, 14, 15, 12,

            // Top face
            16, 17, 18, 18, 19, 16,

            // Bottom face
            20, 21, 22, 22, 23, 20

    };

    uvs = {
        
            // Back face
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            // Front face
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            // Right face
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            // Left face
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            // Top face
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            // Bottom face
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
    
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);           // 3 VBOs: vertices, UVs, instance positions
    glGenBuffers(1, &EBO);          // Create an Element Buffer Object
    glGenBuffers(1, &instanceVBO);  // For instanced positions (as vec3)

    glBindVertexArray(VAO);

    glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);  // Texture unit 0
    glUniform1i(glGetUniformLocation(programID, "useTexture"), true);     // Make sure useTexture is set to true if you want to use the texture

    // 1. Bind the position data buffer (VBO[0])
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* vertices.size(), vertices.data(), GL_STATIC_DRAW); // .size() works on std::vector
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);  // Position attribute

    // 2. Bind the UV data buffer (VBO[1])
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* uvs.size(), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(2);  // UV attribute

    // 3. Bind the Element Buffer Object (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // 4. Create and bind the instance buffer for positions (vec3)
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* m_instancePositions.size(), nullptr, GL_STREAM_DRAW);  // Allocate space for vec3 data

    // Now send the instance data (only the positions) to the buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3)* m_instancePositions.size(), m_instancePositions.data());

    // Set the attribute pointer for the instance data (vec3 position)
    glEnableVertexAttribArray(3);  // Enable the instance position attribute
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glVertexAttribDivisor(3, 1);   // Apply the attribute once per instance, not per vertex

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  // Unbind VAO

}



void Mesh::updateInstanceBuffer(const std::vector<glm::vec3>& instanceData) {
    m_instancePositions = instanceData;  // Update the instance data

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    // Allocate or re-allocate buffer with new size
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_instancePositions.size(), m_instancePositions.data(), GL_DYNAMIC_DRAW);

    // Re-enable attribute pointer after reallocation (sometimes needed)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glVertexAttribDivisor(3, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Mesh::Render(GLuint programID, glm::mat4 viewProjection) {
    glUseProgram(programID);

    glUniform1i(glGetUniformLocation(programID, "useTexture"), GL_TRUE);
    glUniformMatrix4fv(glGetUniformLocation(programID, "viewProjection"), 1, GL_FALSE, &viewProjection[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, m_instancePositions.size());
    glBindVertexArray(0);


    
}







