#ifndef HARDWARE_RENDERER_H
#define HARDWARE_RENDERER_H

#include "build_type.h"

#ifdef HARDWARE_BUILD

#include <stdio.h>
#include <stdlib.h>

#include "default.h"
#include "ST7567_driver.h"

struct renderer {
    unsigned char* backbuffer;
    unsigned char* frontbuffer;
};

struct renderer* renderer_new(void);

void render_free(struct renderer* renderer);
void render_swap(struct renderer* renderer);
void render_clear(struct renderer* renderer, int col);
void render_putpixel(struct renderer* renderer, int x, int y, int col);

#endif

#endif
