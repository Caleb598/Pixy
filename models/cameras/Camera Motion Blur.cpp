#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 0.05f;
float yaw = -90.0f;
float pitch = 0.0f;

glm::mat4 view;
glm::mat4 projection;

bool motionBlurEnabled = true;
int motionBlurSamples = 10;

void updateCamera() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    updateCamera();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

void applyMotionBlur(GLuint framebufferTexture, GLuint motionBlurTexture, GLuint motionBlurShader) {
    glUseProgram(motionBlurShader);

    glUniform1i(glGetUniformLocation(motionBlurShader, "motionBlurSamples"), motionBlurSamples);
    glUniform1f(glGetUniformLocation(motionBlurShader, "motionBlurWeight"), 1.0f / motionBlurSamples);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);

    glBindImageTexture(0, motionBlurTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    glDispatchCompute(screenWidth / 16, screenHeight / 16, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Motion Blur Camera", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set viewport size and framebuffer resize callback
    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Motion blur shader setup (shader compilation, uniform setup, etc.)

    // Create framebuffers and textures
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    GLuint framebufferTexture;
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    GLuint motionBlurTexture;
    glGenTextures(1, &motionBlurTexture);
    glBindTexture(GL_TEXTURE_2D, motionBlurTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, nullptr);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render objects using camera matrices (shader setup and object rendering code here)
        // Bind the framebuffer for rendering

        // Swap framebuffers for next frame
        GLuint temp = framebufferTexture;
        framebufferTexture = motionBlurTexture;
        motionBlurTexture = temp;

        // Apply motion blur effect
        if (motionBlurEnabled)
            applyMotionBlur(framebufferTexture, motionBlurTexture, motionBlurShader);

        // Render the motion blurred result to the default framebuffer (screen)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Render a quad with the motion blurred texture

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteTextures(1, &framebufferTexture);
    glDeleteTextures(1, &motionBlurTexture);
    glDeleteFramebuffers(1, &framebuffer);

    // Clean up GLFW resources
    glfwTerminate();
    return 0;
}
