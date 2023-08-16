#ifndef MENU_H
#define MENU_H

#include <stdlib.h>

#include "../core/application.h"
#include "../core/graphics.h"
#include "../core/picos.h"

struct menu {
    struct application** apps;
    int num_apps;

    int loaded;
    int loaded_index;
};

struct menu* menu_new(void);

void menu_load_apps(struct menu* menu,
                    struct application* (**app_gen_list)(void),
                    int app_num);
void menu_open_app(struct menu* menu,
                   int app_index);
void menu_draw(struct menu* menu);
void menu_free(struct menu* menu);
void menu_exit_app(struct menu* menu);

#endif
