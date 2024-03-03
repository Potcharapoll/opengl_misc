#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const unsigned int width = 800;
const unsigned int height = 800;

static GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,   0.1f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};

static GLuint shader_compile(char *path, GLenum type) {
    FILE *f;
    char *txt;
    long len;

    f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "Cannot open file at %s\n", path);
        return 0;
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);

    txt = calloc(1, len);
    assert(txt > 0);

    fseek(f, 0, SEEK_SET);
    fread(txt, 1, len, f);
    fclose(f);
    
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar * const *)&txt, (const GLint*)&len);
    glCompileShader(shader);

    int check;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &check);
    if (check == GL_FALSE) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, NULL, log);
        printf("Failed to compile %s Shader\n%s\n", (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment", log);
    }

    free(txt);
    return shader;
}

int main(void) {
    GLFWwindow *window;

    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(1);
    }
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "opengl_misc", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Faileld to create GLFW window\n");
        glfwTerminate();
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        exit(1);
    }

    GLuint VAO, VBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    GLuint Shader, VertexShader, FragmentShader;
    Shader = glCreateProgram();
    VertexShader = shader_compile("../res/shaders/triangle.vert", GL_VERTEX_SHADER);
    FragmentShader = shader_compile("../res/shaders/triangle.frag", GL_FRAGMENT_SHADER);
    glAttachShader(Shader, VertexShader);
    glAttachShader(Shader, FragmentShader);
    glLinkProgram(Shader);

    int check;
    glGetProgramiv(Shader, GL_LINK_STATUS, &check);
    if (check == GL_FALSE) {
        char log[1024];
        glGetProgramInfoLog(Shader, 1024, NULL, log);
        printf("Failed to link Shader Program\n%s\n",log);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glViewport(0, 0, width, height);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(Shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
