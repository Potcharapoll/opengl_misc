#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"
#include "ui/ui.h"

#include <stdio.h>
#include <stdlib.h>

const unsigned int width = 1280;
const unsigned int height = 760;

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

    glViewport(0, 0, width, height);
    ui_init(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        ui_update(window);
        ui_render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ui_destroy();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
