#ifndef SOFTWARE_KEYBOARD_H
#define SOFTWARE_KEYBOARD_H

#include "build_type.h"

#include <stdlib.h>

#ifdef SOFTWARE_BUILD
#include <SDL2/SDL.h>

struct keyboard {
    unsigned char last_key;
};

struct keyboard* keyboard_new(void);

int keyboard_read(struct keyboard* kb);
void keyboard_free(struct keyboard* kb);

#endif

#endif
