#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"
#include "texture.h"

#include <stdbool.h>

struct Texture texture_create(const char *path, GLenum type, GLenum slot, GLenum format, GLenum pixelType) {
    struct Texture texture = {.type = type, .slot = slot};

    int width, height, n_chnnels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * bytes = stbi_load(path, &width, &height, &n_chnnels, 0);
    glGenTextures(1, &texture.handle);
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(texture.type, texture.handle);

    glTexParameteri(texture.type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texture.type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(texture.type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texture.type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(texture.type, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
    glGenerateMipmap(texture.type);

    stbi_image_free(bytes);
    texture_unbind(texture);
    return texture;
}

void texture_unit(struct Shader shader,const char *uniform, GLuint unit) {
    GLint tex_unit = glGetUniformLocation(shader.handle, uniform);
    shader_activate(shader);
    glUniform1i(tex_unit, unit);
}

void texture_bind(struct Texture self) {
    glActiveTexture(GL_TEXTURE0+self.slot);
    glBindTexture(self.type, self.handle);
}

void texture_unbind(struct Texture self) {
    glBindTexture(self.type, 0);
}

void texture_delete(struct Texture self) {
    glDeleteTextures(1, &self.handle);
}
