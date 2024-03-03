#ifndef TEXTURE_H
#define TEXTURE_H
#include "gfx.h"
#include "shader.h"

struct Texture {
    GLuint handle;
    GLenum type;
    GLuint slot;
};

struct Texture texture_create(const char *path, GLenum type, GLuint slot, GLenum format, GLenum pixelType);
void texture_bind(struct Texture self);
void texture_unit(struct Shader shader, const char *uniform, GLuint unit);
void texture_unbind(struct Texture self);
void texture_delete(struct Texture self);
#endif
