#include "hardware_keyboard.h"

#ifdef HARDWARE_BUILD

struct keyboard* keyboard_new() {
    struct keyboard* nkb = malloc(sizeof(struct keyboard));
    nkb->device = wiringPiI2CSetup(KEYBOARD_I2C_ADDR);
}

int keyboard_read(struct keyboard* kb) {
    return wiringPiI2CRead(kb->device);
}

void keyboard_free(struct keyboard* kb) {
    free(kb);
}

#endif

void null_func6(void) {}
