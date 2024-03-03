#include "ui.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../gfx/shader.h"
#include "cglm/cglm.h"

#include <stdbool.h>
#include <math.h>

static float scale = 1.0f;
static float speed = 1.0f;
static bool initted = false;
static bool auto_scale = false;
static struct VAO vao_triangle;
static struct VBO vbo_triangle;
static struct Shader shader_triangle;
static vec3 color;

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

static void init_triangle() {
    vao_triangle = vao_create();
    vbo_triangle = vbo_create(GL_ARRAY_BUFFER, false);
    shader_triangle = shader_create("../res/shaders/triangle.vert", "../res/shaders/triangle.frag");

    vao_bind(vao_triangle);
    vao_attr(vao_triangle, vbo_triangle, 0, 3, GL_FLOAT, 3*sizeof(vertices[0]), 0);
    vbo_data(vbo_triangle, sizeof(vertices), vertices);

    shader_activate(shader_triangle);
    glUniform1f(glGetUniformLocation(shader_triangle.handle, "scale"), scale);
    glUniform1f(glGetUniformLocation(shader_triangle.handle, "speed"), speed);
    vao_unbind();
    vbo_unbind(vbo_triangle);

    glm_vec3_one(color);
    initted = true;
}

static void destroy_triangle() {
    vao_delete(vao_triangle);
    vbo_delete(vbo_triangle);
    shader_delete(shader_triangle);
    initted = false;
    auto_scale = false;
}

static inline void update_color(void) {
}

void menu_triangle_render(void) {
    if (igButton("<--", (ImVec2){0.0f, 0.0f})) {
        menu_new(&ui.menu, menu_main_render, menu_main_update, destroy_triangle);
    }
    igSliderFloat("Scale", &scale, 0.0f, 10.0f, "%.2f", 0);
    igSliderFloat("Auto-Scale Speed", &speed, 0.0f, 10.0f, "%.2f", 0);
    igSliderFloat3("Triangle Color", &color[0], 0.0f, 1.0f, "%.2f", 0);
    if (igButton("Reset Scale", (ImVec2){0.0f, 0.0f})) scale = 1.0f;
    igSameLine(0, 5.0f);
    if (igButton("Reset Speed", (ImVec2){0.0f, 0.0f})) speed = 1.0f;
    igCheckbox("Auto-Scale", &auto_scale);
}

void menu_triangle_update(void) {
    if (initted == false) init_triangle();
    shader_activate(shader_triangle);
    glUniform3f(glGetUniformLocation(shader_triangle.handle, "color"), color[0], color[1], color[2]);
    glUniform1f(glGetUniformLocation(shader_triangle.handle, "scale"), scale);
    if (auto_scale) 
        glUniform1f(glGetUniformLocation(shader_triangle.handle, "speed"), sin(glfwGetTime()*speed)/2);

    vao_bind(vao_triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
