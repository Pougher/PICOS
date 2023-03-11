#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdio.h>
#include <stdlib.h>

#define INTERRUPT_KEYBOARD 0x00

struct InterruptHandler {
    int (**interrupts)(char*);
};

struct InterruptHandler* interrupt_handler_new(void);

void register_interrupt_handler(struct InterruptHandler* ih,
                               char address,
                               int (*interrupt)(char*));

void interrupt_request(struct InterruptHandler* ih,
                       char address,
                       char* data);

void interrupt_handler_free(struct InterruptHandler* ih);

#endif
