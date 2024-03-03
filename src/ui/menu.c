#include "ui.h"

#include <stdlib.h>

void menu_new(struct Menu **menu, func render, func update, func cleanup) {
    struct Menu *new_menu = malloc(sizeof(struct Menu));
    new_menu->render = render;
    new_menu->update = update;

    if (*menu != NULL) {
        struct Menu *old_menu = *menu;
        *menu = new_menu;
        if (cleanup != NULL) 
            cleanup();
        menu_destroy(&old_menu);
    }
    *menu = new_menu;
}

void menu_destroy(struct Menu **menu) {
    free(*menu);
    *menu = NULL;
}
