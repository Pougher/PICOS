#ifndef UTIL_PICOS_BUFFER_H
#define UTIL_PICOS_BUFFER_H

#include "picos_str.h"

typedef struct picos_buffernode_t {
    _picos_str v;
    struct picos_buffernode_t* next;
    struct picos_buffernode_t* last;
    struct picos_buffernode_t* end;
    int length;
} picos_buffer_t;

#define _picos_buffer picos_buffer_t*

_picos_buffer picos_buffer_new(void);
_picos_buffer picos_buffer_insert(_picos_buffer buff, int index);

void picos_buffer_newline(_picos_buffer buff);
void picos_buffer_free(_picos_buffer buff);

#endif
