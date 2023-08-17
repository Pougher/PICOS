#include "picos_input.h"

_picos_input picos_input_new(void) {
    _picos_input new_input = malloc(sizeof(picos_input_t));
    new_input->text = picos_str_new();
    new_input->draw_cursor = 1;
    new_input->cursor_pos = 0;
    picos_str_set(new_input->text, "", 0);

    return new_input;
}

void picos_input_update(_picos_input input, int keycode) {
    if (keycode == 0x08) {
        if (input->cursor_pos > 0) {
            input->cursor_pos--;
            picos_str_delete(input->text, input->cursor_pos);
        }
    } else {
        picos_str_addch(input->text, keycode);
        input->cursor_pos++;
    }
}

void picos_input_render(_picos_input input, struct renderer* rend,
    int x, int y, int cutoff) {
    if ((int)input->text->len > cutoff) {
        int limit = (input->cursor_pos / cutoff) * cutoff;
        graphics_draw_string(rend, "$", x, y);
        graphics_draw_string(rend, input->text->str + limit, x + 6, y);
        if (input->draw_cursor) {
            graphics_draw_string_inv(rend, " ", x + ((input->cursor_pos % cutoff) * 6) + 6, y);
        }
    }
    else {
        graphics_draw_string(rend, input->text->str, x, y);
        if (input->draw_cursor) {
            graphics_draw_string_inv(rend, " ", x + (input->cursor_pos * 6), y);
        }
    }
}

void picos_input_reset(_picos_input input) {
    picos_str_clear(input->text);
    input->cursor_pos = 0;
}

void picos_input_free(_picos_input input) {
    picos_str_free(input->text);
    free(input);
}
