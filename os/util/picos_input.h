#ifndef UTIL_PICOS_INPUT_H
#define UTIL_PICOS_INPUT_H

#include "picos_str.h"

#include "../../core/renderer.h"
#include "../../core/graphics.h"

typedef struct {
    _picos_str text;
    int cursor_pos;
    int draw_cursor;
} picos_input_t;

#define _picos_input picos_input_t*

_picos_input picos_input_new(void);

// updates the structs fields when a key press is detected
void picos_input_update(_picos_input input, int keycode);

// renders the _picos_input object
void picos_input_render(_picos_input input, struct renderer* rend,
    int x, int y, int cutoff);

// resets a _picos_input object to be reused
void picos_input_reset(_picos_input input);

// frees the memory of the _picos_input object
void picos_input_free(_picos_input input);
#endif
