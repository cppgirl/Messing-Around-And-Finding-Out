#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void shaderInit(char **vertexShader) {
    FILE *fileVar = fopen("shader.vert", "r");

}

const char *vertexShaderSource = "#version 400 core\n"
    "layout (location = 0) in vec3 inPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(inPos, 1.0);\n"
    "}\0";

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
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    unsigned int VBO;
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    GLFWwindow *window = initGLFW();
    int result = 1;

    IF (NULL != window, "No Window")
    IF (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "No GLAD") {
        result = 0;

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        shaderInit();
        
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
