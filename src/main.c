#include "../core/picos.h"
#include "../os/menu.h"
#include "../apps/applist.h"

#include <stdio.h>
#include <stdlib.h>

void menu_test(void) {
    menu_open_app(menu, 0);
}

#ifdef SOFTWARE_BUILD

#include <SDL2/SDL.h>
#include "../core/window.h"

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    struct window* win = window_create("PICOS Emulator", 1280, 640);

    menu = menu_new();
    renderer = renderer_new();
    keyboard = keyboard_new();

    menu_load_apps(menu, APP_LIST, APP_NUM);
    menu_test();


    SDL_ShowWindow(win->window);
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = 0;
                    break;
                }
            }
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        render_clear(renderer, 0);

        if (menu->loaded) {
            menu->apps[menu->loaded_index]->update();
        }

        render_swap(renderer);

        window_send_buffer_emu(win, renderer);
        SDL_Delay(16);
    }

    window_free(win);
    render_free(renderer);
    menu_free(menu);
    keyboard_free(keyboard);

    return 0;
}

#endif

#ifdef HARDWARE_BUILD

int main(void) {
    ST7567_init();
    ST7567_reset();
    ST7567_begin();

    ST7567_contrast(40);
    ST7567_set_backlight(1);

    menu = menu_new();
    renderer = renderer_new();
    keyboard = keyboard_new();

    menu_load_apps(menu, APP_LIST, APP_NUM);
    menu_test();

    while (1) {
        render_clear(renderer, 0);

        if (menu->loaded) {
            menu->apps[menu->loaded_index]->update();
        }

        render_swap(renderer);
        ST7567_show(renderer->frontbuffer);
        delay(16);
    }

    render_free(renderer);
    menu_free(menu);
    keyboard_free(keyboard);

    return 0;
}

#endif
