#include "window.h"

#ifdef SOFTWARE_BUILD

struct window* window_create(char* title, int w, int h) {
    struct window* win = malloc(sizeof(struct window));
    win->width = w;
    win->height = h;

    win->title = malloc(strlen(title));
    strcpy(win->title, title);

    SDL_CreateWindowAndRenderer(w, h, 0, &win->window, &win->renderer);
    SDL_SetWindowTitle(win->window, title);
    SDL_ShowWindow(win->window);

    return win;
}

void window_send_buffer_emu(struct window* win, struct renderer* renderer) {
    SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
    SDL_RenderClear(win->renderer);

    for (int i = 0; i < SCREEN_WIDTH ; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            SDL_Rect r;
            r.x = i * 10;
            r.y = j * 10;
            r.w = 10;
            r.h = 10;
            if (renderer->frontbuffer[i + j * SCREEN_WIDTH]) {
                SDL_SetRenderDrawColor(win->renderer, 45, 64, 2, 0);
            } else {
                SDL_SetRenderDrawColor(win->renderer, 174, 174, 0, 255);
            }
            SDL_RenderFillRect(win->renderer, &r);
        }
    }

    // draw the grid overlay
    SDL_SetRenderDrawColor(win->renderer, 174, 174, 0, 255);
    for (int i = 0; i < win->height / 10; i++) {
        SDL_RenderDrawLine(win->renderer, 0, i * 10, win->width, i * 10);
    }
    for (int i = 0; i < win->width / 10; i++) {
        SDL_RenderDrawLine(win->renderer,
                           i * 10, 0,
                           i * 10, win->height);
    }

    SDL_RenderPresent(win->renderer);
}

void window_free(struct window* window) {
    free(window->title);

    SDL_DestroyWindow(window->window);
    SDL_DestroyRenderer(window->renderer);
    SDL_Quit();

    free(window);
}

#endif

void null_func_2(void) {}
