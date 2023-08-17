#include "graphics.h"

void graphics_draw_string(struct renderer* rend, char* str, int x_, int y) {
    // draws some text at an X Y position using the default 8x6 font
    int x_loc = 0;

    for (unsigned long i = 0; i < strlen(str); i++) {
        switch (str[i])  {
            case '\n': {
                x_loc = 0;
                y += 8;
                continue;
                break;
            }
            case '\t': {
                x_ += (i * 12);
                continue;
                break;
            }
        }
        for (int x = 0; x < 8; x++) {
            for (int j = 7; j >= 2; j--) {
                render_putpixel(
                    rend,
                    j + x_loc + x_ - 2,
                    y + x,
                    (font6x8[(int)str[i]][x] >> j) & 1
                );
            }
        }
        x_loc += 6;
    }
}

void graphics_draw_string_inv(struct renderer* rend, char* str, int x_, int y) {
    // draws some text at an X Y position using the default 8x6 font
    // inverts the text
    int x_loc = 0;

    for (unsigned long i = 0; i < strlen(str); i++) {
        switch (str[i])  {
            case '\n': {
                y += 8;
                x_loc = 0;
                continue;
                break;
            }
            case '\t': {
                x_ += (i * 12);
                continue;
                break;
            }
        }
        for (int x = 0; x < 8; x++) {
            for (int j = 7; j >= 2; j--) {
                render_putpixel(
                    rend,
                    j + x_loc + x_ - 2,
                    y + x,
                    (~(font6x8[(int)str[i]][x] >> j)) & 1
                );
            }
        }
        x_loc += 6;
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

void graphics_draw_bytemap(struct renderer* rend,
                           char** bitmap,
                           int cols,
                           int rows,
                           int x,
                           int y) {
    for (int i = 0; i < rows; i++) {
        for (int byte = 0; byte < cols; byte++) {
            // iterate over the bits in the byte
            for (int bit = 0; bit < 8; bit++) {
                int val = bitmap[i][byte] & (0x80 >> bit);
                render_putpixel(rend, byte*8 + bit + x, i + y, val);
            }
        }
    }
}

void graphics_draw_bytemap_inv(struct renderer* rend,
                               char** bitmap,
                               int cols,
                               int rows,
                               int x,
                               int y) {
    for (int i = 0; i < rows; i++) {
        for (int byte = 0; byte < cols; byte++) {
            // iterate over the bits in the byte
            for (int bit = 0; bit < 8; bit++) {
                int val = (bitmap[i][byte] & (0x80 >> bit));
                render_putpixel(rend, byte*8 + bit + x, i + y, (~val) & 0x80 >> bit);
            }
        }
    }
}

void graphics_draw_line(struct renderer* rend, int x1, int y1, int x2, int y2) {
    // draws a line from (x1, y1) to (x2, y2)
    int dx = x2 - x1;
    int dy = y2 - y1;
    int D = 2 * dy - dx;
    int y = y1;

    for (int x = x1; x < x2; x++) {
        render_putpixel(rend, x, y, 1);
        if (D > 0) {
            y = y + 1;
            D = D - 2 * dx;
        }
        D = D + 2*dy;
    }
}
