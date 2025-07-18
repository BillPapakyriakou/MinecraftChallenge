
#include "Camera.h"
#include "Matrices.h" 


Camera::Camera(Matrices* matrices)
    :position(glm::vec3(0.0f, 0.0f, 10.0f)),
    orientation(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    matrices(matrices) {
    updateViewMatrix();
}


void Camera::updateViewMatrix() {
    // Normalize the orientation to avoid any issues during movement
    orientation = glm::normalize(orientation);

    // Make sure the view matrix reflects the updated position and orientation
    glm::mat4 viewMatrix = glm::lookAt(position, position + orientation, up);

    // Set the new view matrix
    matrices->setViewMatrix(viewMatrix);

}



void Camera::handleMovement(GLFWwindow* window) {
    /*
    // Adjust speed with left shift key
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 0.4f;
    }
    else {
        speed = 0.1f;
    }
    */
    // Handle key inputs for movement (move in direction of orientation and cross product with up)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        move(speed * orientation);  // Move forward
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        move(speed * -glm::normalize(glm::cross(orientation, up)));  // Move left
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        move(speed * -orientation);  // Move backward
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        move(speed * glm::normalize(glm::cross(orientation, up)));  // Move right
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        move(speed * up);  // Move up
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        move(speed * -up);  // Move down
    }

    // Handle mouse inputs for looking around (mouse input for rotation)
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hide the mouse cursor when the camera is moving
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevent the camera from jumping on the first click
        if (firstClick) {
            glfwSetCursorPos(window, width / 2, height / 2);
            firstClick = false;
        }

        // Get the cursor position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalize and shift the cursor coordinates to the center of the screen, and convert them into degrees
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;


        // Generate the rotation matrix for vertical (pitch) change
        glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        // Apply rotation to orientation as a vector
        glm::vec3 newOrientationY = glm::vec3(rotationMatrixY * glm::vec4(orientation, 0.0f));  // Apply matrix to vector (using 4D homogeneous coordinates)

        // Calculate the cosine of the angle between newOrientation and up
        float cosAngle = glm::dot(glm::normalize(newOrientationY), glm::normalize(up));

        // Calculate the angle in radians
        float angle = glm::acos(cosAngle);

        // Check if the angle is within the range [-85°, 85°]
        if (pitch >= -35.0f && pitch <= 35.0f) {
            orientation = newOrientationY;
        }


        // Generate the rotation matrix for vertical (pitch) change
        glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(-rotY), up);

        // Apply rotation to orientation as a vector
        glm::vec3 newOrientationX = glm::vec3(rotationMatrixX * glm::vec4(orientation, 0.0f));  // Apply matrix to vector (using 4D homogeneous coordinates)
        orientation = newOrientationX;

        // Recenter the mouse cursor to avoid it roaming around
        glfwSetCursorPos(window, width / 2, height / 2);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Unhide the mouse cursor when the camera stops moving
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Reset the first click flag to prevent jumping on the next mouse click
        firstClick = true;
    }

    // Update the camera's view matrix with the new orientation
    updateViewMatrix();
}

 

void Camera::move(const glm::vec3& offset) {
    position += offset;
    updateViewMatrix();
}

void Camera::rotate(float angle, const glm::vec3& axis) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    orientation = glm::mat3(rotation) * orientation;
    orientation = glm::normalize(orientation);
    updateViewMatrix();
}

void Camera::setPosition(const glm::vec3& newPos) {
    position = newPos;
    updateViewMatrix();
}

void Camera::setOrientation(const glm::vec3& newOrientation) {
    orientation = glm::normalize(newOrientation);
    updateViewMatrix();
}

void Camera::setUp(const glm::vec3& newUp) {
    up = glm::normalize(newUp);
    updateViewMatrix();
}
