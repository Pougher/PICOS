#include "graphics.h"

void graphics_draw_string(struct renderer* rend, char* str, int x_, int y) {
    // draws some text at an X Y position using the default 8x6 font
    for (unsigned long i = 0; i < strlen(str); i++) {
        for (int x = 0; x < 8; x++) {
            for (int j = 7; j >= 2; j--) {
                rend->backbuffer
                    [(x * 128) + j + (i * 6) + x_ + y * SCREEN_WIDTH] =
                    (font6x8[(int)str[i]][x] >> j) & 1;
            }
        }
    }
}

void graphics_draw_pixel(struct renderer* rend, int x, int y, int c) {
    // plots a pixel at X Y and makes it colour c (1 = black, 0 = white)
    rend->backbuffer[x + y * SCREEN_WIDTH] = c;
}

void graphics_draw_bitmap_fs(struct renderer* rend, char bitmap[128][64]) {
    // draws a full-screen bitmap
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 64; j++) {
            rend->backbuffer[i + j * SCREEN_WIDTH] = bitmap[i][j];
        }
    }
}

void graphics_draw_bitmap(struct renderer* rend,
                          char* bitmap,
                          int size_x,
                          int size_y,
                          int x,
                          int y) {
    // draws a bitmap inside of a bounding rectangle using the provided data
    for (int i = x; i < size_x + x; i++) {
        for (int j = y; j < size_y + y; j++) {
            rend->backbuffer[i + j * SCREEN_WIDTH] =
                bitmap[(i - x) + (j - y) * size_x];
        }
    }
}
