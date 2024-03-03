#ifndef UI_H
#define UI_H
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "../gfx/gfx.h"
#include "cimgui.h"
#include "cimgui_impl.h"

typedef void (*func)(void);

struct Menu {
    func render, update;
};

struct UI {
    ImGuiContext *ctx;
    ImGuiIO *io;

    struct Menu *menu;
};

void ui_init(GLFWwindow *window);
void ui_render(void);
void ui_update(GLFWwindow *window);
void ui_destroy(void);

void menu_new(struct Menu **menu, func render, func update, func cleanup);
void menu_destroy(struct Menu **menu);
void menu_main_render(void);
void menu_main_update(void);
void menu_triangle_render(void);
void menu_triangle_update(void);
void menu_rectangle_render(void);
void menu_rectangle_update(void);

extern struct UI ui;
#endif
