#include "software_keyboard.h"

#ifdef SOFTWARE_BUILD

struct keyboard* keyboard_new(void) {
    // allocates 128 + 8 bytes of memory to hold the keyboard struct
    struct keyboard* kb = malloc(sizeof(struct keyboard));
    kb->keys = malloc(128);
    return kb;
}

void poll_keyboard(struct keyboard* kb) {
    // polls the keyboard for pressed keys
    SDL_PumpEvents();
    const unsigned char* keys = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < 128; i++) {
        int keycode = SDL_GetKeyFromScancode(i);
        if (keycode < 128) {
            kb->keys[keycode] = keys[i];
        }
    }
}

void keyboard_free(struct keyboard* kb) {
    // frees the keyboard struct
    free(kb->keys);
    free(kb);
}

#endif

void null_func5(void) {}
