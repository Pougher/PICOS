#ifndef HARDWARE_KEYBOARD_H
#define HARDWARE_KEYBOARD_H

#include "build_type.h"
#ifdef HARDWARE_BUILD

struct keyboard {
    char keys[128];
};

#endif

#endif
