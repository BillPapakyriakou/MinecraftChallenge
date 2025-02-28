#pragma once

#include "Common.h"

class Camera;  // Forward declaration of Camera

class Matrices {

private:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;

public:
    Matrices();

    void initializeScene();

    void setModelMatrix(const glm::mat4& matrix);
    void setViewMatrix(const glm::mat4& matrix);
    void setProjectionMatrix(const glm::mat4& matrix);
    void setViewProjectionMatrix(const glm::mat4& matrix);

    glm::mat4 getModelMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getMVP() const;
    glm::mat4 getViewProjectionMatrix() const;
};
