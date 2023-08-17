#include "software_keyboard.h"

#ifdef SOFTWARE_BUILD

struct keyboard* keyboard_new(void) {
    struct keyboard* kb = malloc(sizeof(struct keyboard));
    kb->last_key = 0;
    return kb;
}

int keyboard_read(struct keyboard* kb) {
    // polls the keyboard for pressed keys
    SDL_PumpEvents();
    const unsigned char* keys = SDL_GetKeyboardState(NULL);
    int found_key = 0;
    for (int i = 0; i < 128; i++) {
        int keycode = SDL_GetKeyFromScancode(i);
        if (keys[i]) {
            found_key = 1;
            if (keycode != kb->last_key) {
                kb->last_key = keycode;
                return keycode;
            }
        }
    }
    if (!found_key) kb->last_key = 0;
    return 0;
}

void keyboard_free(struct keyboard* kb) {
    // frees the keyboard struct
    free(kb);
}

#endif

void null_func5(void) {}
