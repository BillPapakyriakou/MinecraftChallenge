#pragma once

#include "Common.h"

#include "Matrices.h" 


class Camera {

private:
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 up;

    Matrices* matrices;  // Pointer to Matrices for synchronization

    void updateViewMatrix();

public:

    // Add yaw and pitch for rotation
    float yaw;
    float pitch;



    // Prevents the camera from jumping around when first clicking left click
    bool firstClick = true;

    // Stores the width and height of the window
    int width = 1000;
    int height = 800;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.5f;
    float sensitivity = 100.0f;


    Camera(Matrices* matrices);

    void handleMovement(GLFWwindow* window);

    void move(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getOrientation() const { return orientation; }
    glm::vec3 getUp() const { return up; }

    void setPosition(const glm::vec3& pos);
    void setOrientation(const glm::vec3& ori);
    void setUp(const glm::vec3& upVec);

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + orientation, up);
    }
};
