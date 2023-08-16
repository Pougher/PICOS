#include "pvim.h"

_picos_str pvim_buffer;
_picos_str pvim_cmd_buffer;
_picos_str pvim_status_buffer;
int pvim_mode;
int pvim_statusline_timeout;

struct application* pvim_new(void) {
    struct application* pvim = malloc(sizeof(struct application));

    strcpy(pvim->name, "PVIM");
    strcpy(pvim->description, "Picos VIM Text Editor");

    pvim->begin = pvim_begin;
    pvim->update = pvim_update;

    return pvim;
}

void pvim_begin(void) {
    pvim_buffer = picos_str_new();
    pvim_buffer = picos_str_set(pvim_buffer, "", 0);

    pvim_cmd_buffer = picos_str_new();
    pvim_cmd_buffer = picos_str_set(pvim_cmd_buffer, "", 0);

    pvim_status_buffer = picos_str_new();
    pvim_status_buffer = picos_str_set(pvim_status_buffer, "", 0);

    // 0 = normal
    // 1 = insert
    // 2 = command
    pvim_mode = 0;
    pvim_statusline_timeout = 0;
}

void pvim_update(void) {
    graphics_draw_string(renderer, pvim_buffer->str, 0, 0);

    int input = keyboard_read(keyboard);

    switch(pvim_mode) {
        case 0: {
            graphics_draw_string_inv(renderer, "NORMAL", 0, 56);
            if (input == 'i') pvim_mode = 1;
            if (input == ';') pvim_mode = 2;
            break;
        }
        case 1: {
            graphics_draw_string_inv(renderer, "INSERT", 0, 56);
            if (input == '\033') { pvim_mode = 0; }
            else if (input == 0x0d) { pvim_buffer = picos_str_addch(pvim_buffer, '\n'); }
            else if (input > 0 && input < 128) pvim_buffer = picos_str_addch(pvim_buffer, input);
            break;
        }
        case 2: {
            graphics_draw_string_inv(renderer, "COMMAND", 0, 56);
            graphics_draw_string(renderer, ":", 44, 55);
            graphics_draw_string(renderer, pvim_cmd_buffer->str, 48, 55);
            if (input == 0x0d) {
                pvim_mode = 0;
                if (strcmp(pvim_cmd_buffer->str, "q") == 0) {
                    picos_str_free(pvim_cmd_buffer);
                    picos_str_free(pvim_buffer);
                    picos_str_free(pvim_status_buffer);

                    menu_exit_app(menu);
                } else {
                    picos_str_set(pvim_status_buffer, "INVALID CMD", 11);
                    pvim_statusline_timeout = 60;
                }
            }
            else if (input > 0 && input < 128) pvim_cmd_buffer = picos_str_addch(pvim_cmd_buffer, input);
            break;
        }
    }
    if (pvim_mode != 2 && pvim_statusline_timeout == 0) {
        graphics_draw_string(renderer, "file.txt", 50, 56);
    } else if (pvim_statusline_timeout) {
        graphics_draw_string(renderer, pvim_status_buffer->str, 50, 56);
    }

    if (pvim_statusline_timeout) pvim_statusline_timeout--;
    graphics_draw_line(renderer, 0, 55, 128, 55);
    graphics_draw_line(renderer, 0, 63, 128, 63);
}
