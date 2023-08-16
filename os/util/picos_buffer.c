#include "picos_buffer.h"

_picos_buffer picos_buffer_new(void) {
    _picos_buffer new_buffer = malloc(sizeof(picos_buffer_t));
    new_buffer->next = NULL;
    new_buffer->last = NULL;
    new_buffer->end = new_buffer;

    new_buffer->v = picos_str_new();
    picos_str_set(new_buffer->v, "", 0);

    return new_buffer;
}

void picos_buffer_newline(_picos_buffer buff) {
    _picos_buffer new_buffer = picos_buffer_new();
    buff->end->next = new_buffer;
    new_buffer->last = buff->end;
    buff->end = new_buffer;
}

_picos_buffer picos_buffer_insert(_picos_buffer buff, int index) {
    _picos_buffer save = buff;
    for (int i = 0; i < index; i++) buff = buff->next;

    _picos_buffer new_buffer = picos_buffer_new();
    if (buff == save->end) { save->end = new_buffer; }
    new_buffer->next = buff->next;
    buff->next = new_buffer;
    new_buffer->last = buff;
    new_buffer->next->last = new_buffer;

    return new_buffer;
}

void picos_buffer_free(_picos_buffer buff) {
    _picos_buffer cur = buff->next;
    while (cur != NULL) {
        picos_str_free(buff->v);
        free(buff);
        buff = cur;
        cur = buff->next;
    }
}
