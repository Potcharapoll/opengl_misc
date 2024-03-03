#include "vao.h"
#include "vbo.h"

struct VAO vao_create() {
    struct VAO self;
    glGenVertexArrays(1, &self.handle);
    return self;
}

void vao_unbind() {
    glBindVertexArray(0);
}

void vao_bind(struct VAO self) {
    glBindVertexArray(self.handle);
}

void vao_delete(struct VAO self) {
    glDeleteVertexArrays(1, &self.handle);
}

void vao_attr(struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) {
    vao_bind(self);
    vbo_bind(vbo);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (const void*)offset);
    glEnableVertexAttribArray(index);
}
