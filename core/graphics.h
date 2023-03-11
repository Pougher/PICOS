#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string.h>

#include "renderer.h"
#include "6x8font.h"

void graphics_draw_string(struct renderer* rend, char* str, int x_, int y);
void graphics_draw_pixel(struct renderer* rend, int x, int y, int c);
void graphics_draw_bitmap_fs(struct renderer* rend, char bitmap[128][64]);
void graphics_draw_bitmap(struct renderer* rend,
                          char* bitmap,
                          int size_x,
                          int size_y,
                          int x,
                          int y);

#endif
