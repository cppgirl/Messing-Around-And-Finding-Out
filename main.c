#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex{
    float pos[3];
    float color[3];
};

static char *copyFileContent(const char *filename) {
    char *buffer = NULL;
    char c = 0;
    int i = 0;
    int lines = 0;

    FILE *fileVar = fopen(filename, "rw");

    if (NULL == fileVar) {
        printf("\n%s not opened :(\n", filename);
    }

    fseek(fileVar, 0, SEEK_END);
    lines = ftell(fileVar);
    buffer = malloc(sizeof(char) * (lines + 1));

    fseek(fileVar, 0, SEEK_SET);

    while (EOF != (c = fgetc(fileVar))) {
        buffer[i] = c;
        i += 1;
    }

    buffer[i] = '\0';

    fclose(fileVar);

    return buffer;
}

void shaderInit(unsigned int shaderProgram) {
    int success;
    char infoLog[512];
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //ugly file path to be fixed
    char *vertexShaderSource = copyFileContent("C:/Users/mango/Desktop/JFA The Game/shader.vert");

    glShaderSource(vertexShader, 1, (const char **)&vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    char *vertexShaderSource2 = copyFileContent("C:/Users/mango/Desktop/JFA The Game/shader.frag");
    glShaderSource(fragmentShader, 1, (const char **)&vertexShaderSource2, NULL);
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s\n", infoLog);
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

    GLFWwindow *result = glfwCreateWindow(800, 600, "Mango", NULL, NULL);

    if (result != NULL) {
        glfwMakeContextCurrent(result);
    }

    return result;
}

#define IF(x, y) if (!(x)) { printf("%s\n", y); } else

int main() {
    struct Vertex vertices[] = {
        {
            .pos = {0.5f, -0.5f, 0.0f},  
            .color = {1.0f, 0.0f, 0.0f}
        },
        {
            .pos = {-0.5f, -0.5f, 0.0f},  
            .color = {0.0f, 1.0f, 0.0f}
        },
        {
            .pos = {0.0f, 0.5f, 0.0f},  
            .color = {0.0f, 0.0f, 1.0f}
        }
    };
    unsigned int VBO;
    GLFWwindow *window = initGLFW();
    int result = 1;
    unsigned int VAO;
    unsigned int shaderProgram;

    IF (NULL != window, "No Window")
    IF (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "No GLAD") {
        result = 0;

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        shaderProgram = glCreateProgram();
        shaderInit(shaderProgram);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, pos));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, color));
        glEnableVertexAttribArray(1);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        //glBindVertexArray(0);
        
        glUseProgram(shaderProgram);

        while (!glfwWindowShouldClose(window)) {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }

    glfwTerminate();

    return result;
}
