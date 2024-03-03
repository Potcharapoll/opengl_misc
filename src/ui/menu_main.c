#include "ui.h"

void menu_main_render(void) {
    if (igButton("Triangle", (ImVec2){0.0f, 0.0f})) {
        menu_new(&ui.menu, menu_triangle_render, menu_triangle_update, NULL);
    }
    if (igButton("Rectangle", (ImVec2){0.0f, 0.0f})) {
        menu_new(&ui.menu, menu_rectangle_render, menu_rectangle_update, NULL);
    }
}

void menu_main_update(void) {
    
}
