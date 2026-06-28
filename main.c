#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow *initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *result = glfwCreateWindow(800, 600, "Window Tittle", NULL, NULL);

    if (result != NULL) {
        glfwMakeContextCurrent(result);
    }

    return result;
}

#define IF(x, y) if (!(x)) { printf("%s\n", y); } else

int main() {
    GLFWwindow *window = initGLFW();
    int result = 1;

    IF (NULL != window, "No Window")
    IF (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "No GLAD") {
        result = 0;

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        while (!glfwWindowShouldClose(window)) {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();

    return result;
}
