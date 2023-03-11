#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include "renderer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct window {
    int width;
    int height;
    char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

struct window* window_create(char* title, int w, int h);

void window_send_buffer_emu(struct window* win, struct renderer* renderer);
void window_free(struct window* window);

#endif
