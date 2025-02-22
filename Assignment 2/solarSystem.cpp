#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

// Camera variables
float cameraZoom = 1.0f;
float cameraRotation = 0.0f;
float cameraPan = 0.0f;

// Function to draw a circle
void drawCircle(float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the circle
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to render the solar system
void renderSolarSystem(float time) {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Apply camera transformations
    glScalef(cameraZoom, cameraZoom, 1.0f);
    glRotatef(cameraRotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(cameraPan, 0.0f, 0.0f);

    // Draw Sunins
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    drawCircle(0.2f, 100);

    // Draw Earth orbiting the Sun
    float x = 0.8f * cos(time);
    float y = 0.6f * sin(time);
    //glRotatef(time * 50.0f, 0.0f, 0.0f, 1.0f); // Rotate Earth
    glTranslatef(0.8f / 2, 0.0f, 0.0f); // Move Earth away from Sun half of the way of the semi-major so it is on a focal point
    //new method using x y coordinates
    glTranslatef(x, y, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for Earth
    drawCircle(0.1f, 100);

    // Draw Moon orbiting the Earth
    glRotatef(time * 100.0f, 0.0f, 0.0f, 1.0f); // Rotate Moon
    glTranslatef(0.2f, 0.0f, 0.0f); // Move Moon away from Earth
    glColor3f(0.8f, 0.8f, 0.8f); // Gray color for Moon
    drawCircle(0.05f, 50);

    glPopMatrix(); // Return to Sun's transformation stack

    glPushMatrix(); //save it again for later

    // Draw Mars orbiting the sun
    glRotatef(time * 25.0f, 0.0f, 0.0f, 1.0f); // Rotate Mars
    glTranslatef(1.0f, 0.0f, 0.0f); // Move Mars away from Sun
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for mars
    drawCircle(0.05f, 50);

    // Draw Mars moon orbiting mars
    glRotatef(time * 50.0f, 0.0f, 0.0f, 1.0f); // Rotate
    glTranslatef(0.2f, 0.0f, 0.0f); // Move
    glColor3f(0.6f, 0.6f, 0.6f); // Color
    drawCircle(0.025f, 50);

    glPopMatrix();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_W:
            cameraZoom += 0.1f;
            break;
        case GLFW_KEY_S:
            cameraZoom -= 0.1f;
            if (cameraZoom < 0.1f) cameraZoom = 0.1f;
            break;
        case GLFW_KEY_E:
            cameraRotation += 5.0f;
            break;
        case GLFW_KEY_Q:
            cameraRotation -= 5.0f;
            break;
        case GLFW_KEY_A:
            cameraPan += 0.1f;
            break;
        case GLFW_KEY_D:
            cameraPan -= 0.1f;
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System Simulation", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set key callback
    glfwSetKeyCallback(window, keyCallback);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate elapsed time
        float time = (float)glfwGetTime();

        // Render the solar system
        renderSolarSystem(time);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
