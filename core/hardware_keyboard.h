#ifndef HARDWARE_KEYBOARD_H
#define HARDWARE_KEYBOARD_H

#include "build_type.h"
#ifdef HARDWARE_BUILD

#include <wiringPiI2C.h>

struct keyboard {
    int device;
};

struct keyboard* keyboard_new();

int keyboard_read(struct keyboard* kb);

void keyboard_read(struct keyboard* kb);

#endif

#endif
