#ifndef HARDWARE_KEYBOARD_H
#define HARDWARE_KEYBOARD_H

#include "build_type.h"
#ifdef HARDWARE_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <wiringPiI2C.h>

#define KEYBOARD_I2C_ADDR 0x5f

struct keyboard {
    int device;
};

struct keyboard* keyboard_new();

int keyboard_read(struct keyboard* kb);

void keyboard_free(struct keyboard* kb);

#endif

#endif
