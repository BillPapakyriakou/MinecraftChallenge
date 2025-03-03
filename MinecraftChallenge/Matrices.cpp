#include "Matrices.h"
#include "Common.h"

Matrices::Matrices() {
    model = glm::mat4(1.0f);  // Identity matrix
    view = glm::mat4(1.0f);   // Identity matrix
    projection = glm::mat4(1.0f);  // Identity matrix
    viewProjection = projection * view;  // Combine the two to create the final viewProjection matrix
}

// Initialize matrices with default values
void Matrices::initializeScene() {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    view = glm::lookAt(
        glm::vec3(0.0f, 5.0f, 10.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    projection = glm::perspective(glm::radians(45.0f), 4.0f / 4.0f, 0.1f, 100.0f);
}

// Setter methods
void Matrices::setModelMatrix(const glm::mat4& matrix) { model = matrix; }
void Matrices::setViewMatrix(const glm::mat4& matrix) { view = matrix;}
void Matrices::setProjectionMatrix(const glm::mat4& matrix) { projection = matrix; }
void Matrices::setViewProjectionMatrix(const glm::mat4& matrix) { viewProjection = matrix; }

// Getter methods
glm::mat4 Matrices::getModelMatrix() const { return model; }
glm::mat4 Matrices::getViewMatrix() const { return view; }
glm::mat4 Matrices::getProjectionMatrix() const { return projection; }

glm::mat4 Matrices::getViewProjectionMatrix() const { return viewProjection; }

// MVP matrix
glm::mat4 Matrices::getMVP() const { return projection * view * model; }





