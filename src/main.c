#include "GLFW/glfw3.h"
#include "cglm/cglm.h"
#include <stdlib.h>

int main(void) {
    GLFWwindow *window;

    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(1);
    }
    
    window = glfwCreateWindow(800, 800, "opengl_misc", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Faield to create GLFW window\n");
        glfwTerminate();
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
