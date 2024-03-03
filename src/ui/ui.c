#include "ui.h"
#include "cglm/cglm.h"

struct UI ui;
static char buffer[38];
static vec3 color;

void ui_init(GLFWwindow *window) {
   ui.ctx = igCreateContext(NULL);
   ui.io = igGetIO();
   menu_new(&ui.menu, menu_main_render, menu_main_update, NULL);

   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330 core");
   igStyleColorsDark(NULL);
}

void ui_render(void) {
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void ui_update(GLFWwindow *window) {
    glClearColor(color[0], color[1], color[2], 1.0f);
    snprintf(buffer, 38, "OpenGL_Misc [%.3f ms/frame, %.1f FPS]", 1000.0f/ui.io->Framerate, ui.io->Framerate);
    glfwSetWindowTitle(window, buffer);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    if(ui.menu->update != NULL)
        ui.menu->update();

    igBegin("Menu", NULL, 0);
    igColorEdit3("Screen Color", &color[0], 0);
    ui.menu->render();
    igEnd();

}

void ui_destroy(void) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igShutdown();
    igDestroyContext(ui.ctx);
}
