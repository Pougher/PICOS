#include "graphics.h"

void graphics_draw_string(struct renderer* rend, char* str, int x_, int y) {
    // draws some text at an X Y position using the default 8x6 font
    for (unsigned long i = 0; i < strlen(str); i++) {
        switch (str[i])  {
            case '\n': {
                y += 12;
                break;
            }
            case '\t': {
                x_ += (i * 12);
                break;
            }
        }
        for (int x = 0; x < 8; x++) {
            for (int j = 7; j >= 2; j--) {
                render_putpixel(
                    rend,
                    j + (i * 6) + x_ - 2,
                    y + x,
                    (font6x8[(int)str[i]][x] >> j) & 1
                );
            }
        }
    }
}

void graphics_draw_string_inv(struct renderer* rend, char* str, int x_, int y) {
    // draws some text at an X Y position using the default 8x6 font
    // inverts the text
    for (unsigned long i = 0; i < strlen(str); i++) {
        switch (str[i])  {
            case '\n': {
                y += 12;
                break;
            }
            case '\t': {
                x_ += (i * 12);
                break;
            }
        }
        for (int x = 0; x < 8; x++) {
            for (int j = 7; j >= 2; j--) {
                render_putpixel(
                    rend,
                    j + (i * 6) + x_ - 2,
                    y + x,
                    (~(font6x8[(int)str[i]][x] >> j)) & 1
                );
            }
        }
    }
}

void graphics_draw_pixel(struct renderer* rend, int x, int y, int c) {
    // in practice, its faster to run render_putpixel directly
    // plots a pixel at X Y and makes it colour c (1 = black, 0 = white)
    render_putpixel(rend, x, y, c);
}

void graphics_draw_bitmap_fs(struct renderer* rend, char bitmap[128][64]) {
    // draws a full-screen bitmap
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 64; j++) {
            render_putpixel(rend, i, j, bitmap[i][j]);
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
            render_putpixel(rend, i, j, bitmap[(i - x) + (j - y) * size_x]);
        }
    }
}
