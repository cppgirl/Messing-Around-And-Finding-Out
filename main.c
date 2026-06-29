#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static char *copyFileContent(const char *filename, int *lines) {
    char *buffer = NULL;
    char c = 0;
    int i = 0;

    FILE *fileVar = fopen(filename, "rw");

    if (NULL == fileVar) {
        printf("\n%s not opened :(\n", filename);
    }

    fseek(fileVar, 0, SEEK_END);
    *lines = ftell(fileVar);
    buffer = malloc(sizeof(char) * (*lines + 1));

    fseek(fileVar, 0, SEEK_SET);

    while (EOF != (c = fgetc(fileVar))) {
        buffer[i] = c;
        i += 1;
    }

    buffer[i] = '\0';

    fclose(fileVar);

    return buffer;
}

void shaderInit() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    int size = 0;
    //ugly file path to be fixed
    char *vertexShaderSource = copyFileContent("C:/Users/mango/Desktop/JFA The Game/shader.vert", &size);

    glShaderSource(vertexShader, 1, (const char **)&vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex shader compilation failed :(\n");
    }

}

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
