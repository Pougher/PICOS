#include "interrupt.h"

struct InterruptHandler* interrupt_handler_new(void) {
    // create a new interrupt handler object
    struct InterruptHandler* ih = malloc(sizeof(struct InterruptHandler));
    // allocate enough space for 256 unique function pointers
    ih->interrupts = malloc(sizeof(void (*)(char)) * 256);
    return ih;
}

void register_interrupt_handler(struct InterruptHandler* ih,
                                char address,
                                int (*interrupt)(char*)) {
    // sets an interrupt address to be a specific interrupt handler
    ih->interrupts[(unsigned int)address] = interrupt;
}

void interrupt_request(struct InterruptHandler* ih,
                       char address,
                       char* data) {
    // calls the interrupt handler at `address` and supplies it with `data`
    ih->interrupts[(unsigned int)address](data);
}
