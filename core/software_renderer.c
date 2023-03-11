#include "software_renderer.h"

#ifdef SOFTWARE_BUILD

struct renderer* renderer_new(void) {
    // allocate a front buffer and a back buffer,
    // allowing for a buffer swap when the scene needs to be rendered.
    struct renderer* renderer = malloc(sizeof(struct renderer));
    renderer->backbuffer = malloc(SCREEN_WIDTH * SCREEN_HEIGHT);
    renderer->frontbuffer = malloc(SCREEN_WIDTH * SCREEN_HEIGHT);

    return renderer;
}

void render_free(struct renderer* renderer) {
    free(renderer->backbuffer);
    free(renderer->frontbuffer);
    free(renderer);
}

void render_swap(struct renderer* renderer) {
    // swap the front and back buffer pointers
    // faster to instantiate another variable than doing the xor swap trick
    unsigned char* temp_buffer = renderer->backbuffer;
    renderer->backbuffer = renderer->frontbuffer;
    renderer->frontbuffer = temp_buffer;
}

void render_clear(struct renderer* renderer, int col) {
    // clears the backbuffer
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        renderer->backbuffer[i] = col;
}

void render_putpixel(struct renderer* renderer, int x, int y, int col) {
    // sets a pixel at a specific coordinate in the backbuffer to `col`
    renderer->backbuffer[x + y * SCREEN_WIDTH] = col;
}

#endif

void null_func_1(void) {} // prevent compiler errors
