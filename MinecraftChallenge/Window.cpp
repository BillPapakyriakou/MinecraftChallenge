#include "Window.h"


Window::Window(const std::string& title, bool fullscreen) {
    
    initializeGLFW(width, height, title, fullscreen);
    initializeGLEW(); // Initialize GLEW after the window is created

    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glClearColor(0.0f, 0.3f, 0.8f, 1.0f); // Background color

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture key presses
}

Window::~Window() {
    glfwDestroyWindow(window);  // Properly destroy window on exit
    glfwTerminate();  // Terminate GLFW
}

void Window::initializeGLFW(int width, int height, const std::string& title, bool fullscreen) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("GLFW initialization failed");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = NULL;
    if (fullscreen) {
        monitor = glfwGetPrimaryMonitor(); // Get primary monitor
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(videoMode->width, videoMode->height, title.c_str(), monitor, NULL); // Fullscreen
    }
    else {
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL); // Windowed
    }

    if (!window) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync
}

void Window::initializeGLEW() const {
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        throw std::runtime_error("GLEW initialization failed");
    }
}

void Window::clearScreen() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
}

void Window::swapBuffers() const {
    glfwSwapBuffers(window); // Swap buffers
}

void Window::pollEvents() const {
    glfwPollEvents(); // Poll for and process events
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window); // Return whether window should close
}

GLFWwindow* Window::getGLFWwindow() const {
    return window; // Return the window object
}

