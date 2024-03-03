#include "ui.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../gfx/shader.h"
#include "cglm/cglm.h"
#include <strings.h>

static float scale = 1.0f;
static float speed = 1.0f;
static bool initted = false;
static bool auto_scale = false;
static struct VAO vao_rectangle;
static struct VBO vbo_rectangle, ebo_rectangle;
static struct Shader shader_rectangle;
static vec3 color;

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

static unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

static void init_rectangle() {
    vao_rectangle = vao_create();
    vbo_rectangle = vbo_create(GL_ARRAY_BUFFER, false);
    ebo_rectangle = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);
    shader_rectangle = shader_create("../res/shaders/rectangle.vert", "../res/shaders/rectangle.frag");

    vao_bind(vao_rectangle);
    vao_attr(vao_rectangle, vbo_rectangle, 0, 3, GL_FLOAT, 3*sizeof(vertices[0]), 0);
    vbo_data(vbo_rectangle, sizeof(vertices), vertices);

    vbo_bind(ebo_rectangle);
    vbo_data(ebo_rectangle, sizeof(indices), indices);

    shader_activate(shader_rectangle);
    glUniform1f(glGetUniformLocation(shader_rectangle.handle, "scale"), scale);
    glUniform1f(glGetUniformLocation(shader_rectangle.handle, "speed"), speed);
    vao_unbind();
    vbo_unbind(vbo_rectangle);
    vbo_unbind(ebo_rectangle);

    glm_vec3_one(color);
    initted = true;
}

static void rectangle_destroy(void) {
    vao_delete(vao_rectangle);
    vbo_delete(vbo_rectangle);
    shader_delete(shader_rectangle);
    initted = false;
    auto_scale = false;
}

void menu_rectangle_render(void) {
    if (igButton("<--", (ImVec2){0.0f, 0.0f})) {
        menu_new(&ui.menu, menu_main_render, menu_main_update, rectangle_destroy);
    }
    igSliderFloat("Scale", &scale, 0.0f, 10.0f, "%.2f", 0);
    igSliderFloat("Auto-Scale Speed", &speed, 0.0f, 10.0f, "%.2f", 0);
    igSliderFloat3("Rectangle Color", &color[0], 0.0f, 1.0f, "%.2f", 0);
    if (igButton("Reset Scale", (ImVec2){0.0f, 0.0f})) scale = 1.0f;
    igSameLine(0, 5.0f);
    if (igButton("Reset Speed", (ImVec2){0.0f, 0.0f})) speed = 1.0f;
    igCheckbox("Auto-Scale", &auto_scale);
}

void menu_rectangle_update(void) {
    if (initted == false) init_rectangle();
    shader_activate(shader_rectangle);
    glUniform3f(glGetUniformLocation(shader_rectangle.handle, "color"), color[0], color[1], color[2]);
    glUniform1f(glGetUniformLocation(shader_rectangle.handle, "scale"), scale);
    if (auto_scale) 
        glUniform1f(glGetUniformLocation(shader_rectangle.handle, "speed"), sin(glfwGetTime()*speed)/2);

    vao_bind(vao_rectangle);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);

}

