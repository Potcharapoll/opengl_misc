#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static GLuint _compile(GLenum type, char *path) {
    FILE *f;
    char *buffer;
    long len;

    f = fopen(path, "rb");
    assert(f != NULL);
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);
    fseek(f, 0, SEEK_SET);
    buffer = calloc(1, len);
    assert(buffer != NULL);
    fread(buffer, 1, len, f);
    assert(strlen(buffer) > 0);
    fclose(f);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar* const*)&buffer, (const GLint*)&len);
    glCompileShader(shader);
    
    GLint check;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &check);
    if (check == GL_FALSE) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, NULL, log);
        printf("Failed to compile %s Shader\n%s\n", (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment", log);
    }

    free(buffer);
    return shader;
} 

struct Shader shader_create(char *vs_path, char *fs_path) {
    struct Shader shader;
    shader.handle = glCreateProgram();
    shader.vs = _compile(GL_VERTEX_SHADER, vs_path);
    shader.fs = _compile(GL_FRAGMENT_SHADER, fs_path);

    glAttachShader(shader.handle, shader.vs);
    glAttachShader(shader.handle, shader.fs);
    glLinkProgram(shader.handle);

    GLint check;
    glGetProgramiv(shader.handle, GL_LINK_STATUS, &check);
    if (check == GL_FALSE) {
        char log[1024];
        glGetProgramInfoLog(shader.handle, 1024, NULL, log);
        printf("Failed to link the Shader Program\n%s\n", log);
    }

    glValidateProgram(shader.handle);
    return shader;
}

void shader_activate(struct Shader shader) {
    glUseProgram(shader.handle);
}

void shader_delete(struct Shader shader) {
    glDeleteShader(shader.vs);
    glDeleteShader(shader.fs);
    glDeleteProgram(shader.handle);
}
