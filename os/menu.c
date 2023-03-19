#include "menu.h"

struct menu* menu_new(void) {
    // allocates a new menu on the heap and returns the pointer
    struct menu* new_menu = malloc(sizeof(struct menu));
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

void menu_draw(struct menu* menu) {
    (void) menu;
    // draws the menu
    graphics_draw_string(renderer, "MENU_TEST", 0, 0);
}

void menu_free(struct menu* menu) {
    // frees all data allocated to menu
    for (int i = 0; i < menu->num_apps; i++) free(menu->apps[i]);
    free(menu->apps);
    free(menu);
}
