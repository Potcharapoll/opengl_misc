#include "vbo.h"

struct VBO vbo_create(GLenum type, bool dynamic) {
    struct VBO self = {.dynamic = dynamic, .type = type};
    glGenBuffers(1, &self.handle);
    return self;
}

void vbo_data(struct VBO self, GLsizeiptr size, const GLvoid *data) {
    glBindBuffer(self.type, self.handle);
    glBufferData(self.type, size, data, self.dynamic == true ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void vbo_bind(struct VBO self) {
    glBindBuffer(self.type, self.handle);
}

void vbo_unbind(struct VBO self) {
    glBindBuffer(self.type, 0);
}

void vbo_delete(struct VBO self) {
    glDeleteBuffers(1, &self.handle);
}
