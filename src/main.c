#include "../core/build_type.h"
#include "../core/graphics.h"
#include "../core/renderer.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef SOFTWARE_BUILD

#include <SDL2/SDL.h>
#include "../core/window.h"

char bitmap[8*8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 1, 0, 0, 0,
    0, 1, 0, 1, 0, 1, 0, 0,
    1, 0, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
};

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    struct window* win = window_create("FoxOS Emulator", 1280, 640);
    struct renderer* rend = renderer_new();

    SDL_ShowWindow(win->window);

    SDL_Event event;
    int running = 1;

    int x = 0;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
        }
        render_clear(rend, 0);
        graphics_draw_string(rend, "PICOS OS 0.1a", x, 0);
        graphics_draw_bitmap(rend, bitmap, 8, 8, 0, 0);
        render_swap(rend);

        window_send_buffer_emu(win, rend);
        SDL_Delay(16);

        x = (x + 1) % 128;
    }

    window_free(win);

    return 0;
}

#endif

#ifdef HARDWARE_BUILD

int main(void) {
    printf("HARDWARE BUILD SUCCEED!\n");
    return 0;
}

#endif
