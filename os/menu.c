#include "menu.h"

struct menu* menu_new(void) {
    // allocates a new menu on the heap and returns the pointer
    struct menu* new_menu = malloc(sizeof(struct menu));
    new_menu->loaded = 0;
    new_menu->cursor_index = 0;
    return new_menu;
}

void menu_load_apps(struct menu* menu,
                    struct application* (**app_gen_list)(void),
                    int app_num) {
    // loads all apps from a list into a menu struct
    menu->num_apps = app_num;
    menu->apps = malloc(sizeof(struct application) * app_num);
    for (int i = 0; i < app_num; i++) {
        menu->apps[i] = app_gen_list[i]();
    }
}

void menu_open_app(struct menu* menu,
                   int app_index) {
    // opens a specific app at app_index
    menu->loaded = 1;
    menu->loaded_index = app_index;

    menu->apps[app_index]->begin();
}

void menu_exit_app(struct menu* menu) {
    menu->loaded = 0;
}

void menu_draw(struct menu* menu) {
    // draws the menu
    for (int i = 0; i < menu->num_apps; i++) {
        if (i == menu->cursor_index) {
            graphics_draw_bytemap_inv(renderer, menu->apps[i]->icon, 4, 19, 0, 0);
        } else {
            graphics_draw_bytemap(renderer, menu->apps[i]->icon, 4, 19, 0, 0);
        }
    }
}

void menu_update(struct menu* menu) {
    int input = keyboard_read(keyboard);
    if (input == 0x0d) menu_open_app(menu, menu->cursor_index);
}

void menu_free(struct menu* menu) {
    // frees all data allocated to menu
    for (int i = 0; i < menu->num_apps; i++) application_free(menu->apps[i]);
    free(menu->apps);
    free(menu);
}
