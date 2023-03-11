#ifndef SOFTWARE_RENDERER_H
#define SOFTWARE_RENDERER_H

#include "build_type.h"

#ifdef SOFTWARE_BUILD

#include <stdio.h>
#include <stdlib.h>

#include "default.h"

struct renderer {
    unsigned char* backbuffer;
    unsigned char* frontbuffer;
};

struct renderer* renderer_new(void);

void render_free(struct renderer* renderer);
void render_swap(struct renderer* renderer);
void render_clear(struct renderer* renderer, int col);

#endif

#endif
