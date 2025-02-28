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
    /*

    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);           // 3 VBOs: vertices, UVs, instance positions
    glGenBuffers(1, &EBO);          // Create an Element Buffer Object
    glGenBuffers(1, &instanceVBO);  // For instanced positions


    glBindVertexArray(VAO);

    glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);  // Texture unit 0
    glUniform1i(glGetUniformLocation(programID, "useTexture"), true);     // Make sure useTexture is set to true if you want to use the texture

    // 1. Bind the position data buffer (VBO[0])
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW); // .size() works on std::vector
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);  // Position attribute
    

    // 2. Bind the UV data buffer (VBO[1])
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* uvs.size(), uvs.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvData.size(), uvData.data(), GL_STATIC_DRAW); // .size() works on std::vector
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(2);  // UV attribute


    // 3. Bind the Element Buffer Object (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


    // 4. Create and bind the instance buffer for matrices (for each block)
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_instancePositions.size(), nullptr, GL_STREAM_DRAW);  // Allocate space for mat4 data

    // Now we split each mat4 into 4 vec4s
    for (size_t i = 0; i < m_instancePositions.size(); ++i) {
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::mat4), sizeof(glm::mat4), &m_instancePositions[i]);
    }

    // Set the attribute pointer for the instance data (mat4 split into 4 vec4s)
    for (int i = 0; i < 4; ++i) {
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(i * sizeof(glm::vec4)));
        glEnableVertexAttribArray(3 + i);  // Enable each vec4 component
        glVertexAttribDivisor(3 + i, 1);   // Tell OpenGL it's per-instance data
    }

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  // Unbind VAO
    */

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
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(3);  // Enable the instance position attribute
    glVertexAttribDivisor(3, 1);   // Apply the attribute once per instance, not per vertex

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  // Unbind VAO

}


void Mesh::updateInstanceBuffer(const std::vector<glm::vec3>& instanceData) {
    m_instancePositions = instanceData;  // Update the instance data

    // Update the instance VBO with new position data
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4) * m_instancePositions.size(), m_instancePositions.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
}

/*
void Mesh::Render(GLuint programID, glm::mat4 viewProjection) {
    glUseProgram(programID);

    // Before rendering
    GLuint useTextureLocation = glGetUniformLocation(programID, "useTexture");
    glUniform1i(useTextureLocation, GL_TRUE); // Enable texture usage

    // Pass the viewProjection matrix to the shader
    GLuint viewProjLocation = glGetUniformLocation(programID, "viewProjection");
    glUniformMatrix4fv(viewProjLocation, 1, GL_FALSE, &viewProjection[0][0]);

    // Pass the MVP matrix for each instance
    GLuint mvpLocation = glGetUniformLocation(programID, "MVP");

    for (const glm::vec3& position : m_instancePositions) {
        glm::mat4 Model = glm::translate(glm::mat4(1.0f), position);  // Apply the instance position to the model matrix
        glm::mat4 MVP = viewProjection * Model;  // Combine viewProjection with the model matrix

        // Pass the MVP matrix to the shader for each instance
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &MVP[0][0]);


        // Bind the texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);

        // Bind VAO and draw the instances
        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, m_instancePositions.size());
    }

    glBindVertexArray(0);
}
*/
void Mesh::Render(GLuint programID, glm::mat4 viewProjection) {
    glUseProgram(programID);

    // Enable textures if necessary
    GLuint useTextureLocation = glGetUniformLocation(programID, "useTexture");
    glUniform1i(useTextureLocation, GL_TRUE); // Enable texture usage

    // Pass the viewProjection matrix to the shader
    GLuint viewProjLocation = glGetUniformLocation(programID, "viewProjection");
    glUniformMatrix4fv(viewProjLocation, 1, GL_FALSE, &viewProjection[0][0]);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);

    // Bind VAO for the mesh (this has the VBOs, EBO, and other state)
    glBindVertexArray(VAO);

    // Update the instance data (we're updating the VBO with the new instance data)
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4) * m_instancePositions.size(), m_instancePositions.data());

    // Now draw the mesh with instancing
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, m_instancePositions.size());
    std::cout << "DrawnElements " << m_instancePositions.size() << std::endl;
    // Cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}






