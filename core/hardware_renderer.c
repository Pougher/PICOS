#include "hardware_renderer.h"

#ifdef HARDWARE_BUILD

struct renderer* renderer_new(void) {
    // allocate a front and back buffer.
    // unlike the software renderer, this allocates a buffer that is 1/8th of
    // the size.
    struct renderer* renderer = malloc(sizeof(struct renderer));
    renderer->backbuffer = malloc((SCREEN_WIDTH * SCREEN_HEIGHT) / 8);
    renderer->frontbuffer = malloc((SCREEN_WIDTH * SCREEN_HEIGHT) / 8);

    return renderer;
}

void render_free(struct renderer* renderer) {
    free(renderer->backbuffer);
    free(renderer->frontbuffer);
    free(renderer);
}

void render_swap(struct renderer* renderer) {
    // swap the front and back buffers
    unsigned char* temp_buffer = renderer->backbuffer;
    renderer->backbuffer = renderer->frontbuffer;
    renderer->frontbuffer = temp_buffer;
}

void render_clear(struct renderer* renderer, int col) {
    // clears the backbuffer
    for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT) / 8; i++)
        renderer->backbuffer[i] = 0x00;
}

void render_putpixel(struct render* renderer, int x, int y, int col) {
    int offset = ((y / 8) * WIDTH) + x;
    int bit    = y % 8;
    renderer->backbuffer[offset] &= ~(1 << bit);
    renderer->backbuffer[offset] |= (value & 1) << bit;
}

#endif

void null_func(void) {}
