#ifndef VBO_H
#define VBO_H
#include "gfx.h"
#include <stdbool.h>

struct VBO {
    GLenum type;
    GLuint handle;
    bool dynamic;
};

struct VBO vbo_create(GLenum type, bool dynamic);
void vbo_data(struct VBO self, GLsizeiptr size, const GLvoid *data);
void vbo_bind(struct VBO self);
void vbo_unbind(struct VBO self);
void vbo_delete(struct VBO self);
#endif
