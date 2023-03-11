#include "../core/picos.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef SOFTWARE_BUILD

#include <SDL2/SDL.h>
#include "../core/window.h"

char gdata[20] = { 0 };
int data_ptr = 0;

int keycode_handler(char* data) {
    gdata[data_ptr] = data[0];
    data_ptr++;
    return 1;
}

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    struct window* win = window_create("PICOS Emulator", 1280, 640);
    renderer = renderer_new();
    interrupt_handler = interrupt_handler_new();

    // register key handler
    register_interrupt_handler(interrupt_handler,
                               INTERRUPT_KEYBOARD,
                               keycode_handler);

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
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym < 0x80) {
                        // ascii key character
                        interrupt_request(interrupt_handler,
                                          INTERRUPT_KEYBOARD,
                                          (char[]) {
                                          (char)event.key.keysym.sym}
                                          );
                    }
                    break;
                }
            }
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        render_clear(renderer, 0);
        graphics_draw_string(renderer, gdata, 0, 0);
        render_swap(renderer);

        window_send_buffer_emu(win, renderer);
        SDL_Delay(16);
    }

    window_free(win);
    interrupt_handler_free(interrupt_handler);
    render_free(renderer);

    return 0;
}

#endif

#ifdef HARDWARE_BUILD

int main(void) {
    printf("HARDWARE BUILD SUCCEED!\n");
    return 0;
}

#endif
