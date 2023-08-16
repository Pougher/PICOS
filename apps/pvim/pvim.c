#include "pvim.h"

_picos_str pvim_buffer;
int pvim_mode;

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

    // 0 = normal
    // 1 = insert
    // 2 = command
    pvim_mode = 0;
}

void pvim_update(void) {
    graphics_draw_string(renderer, "file.txt", 50, 56);
    graphics_draw_string(renderer, pvim_buffer->str, 0, 0);
    graphics_draw_line(renderer, 0, 55, 128, 55);
    graphics_draw_line(renderer, 0, 63, 128, 63);

    char input = keyboard_read(keyboard);

    switch(pvim_mode) {
        case 0: {
            graphics_draw_string_inv(renderer, "NORMAL", 0, 56);
            if (input == 'i') pvim_mode = 1;
            if (input == ':') pvim_mode = 2;
            if (input == 'q') {
                picos_str_free(pvim_buffer);
                menu_exit_app(menu);
            }
            break;
        }
        case 1: {
            graphics_draw_string_inv(renderer, "INSERT", 0, 56);
            if (input == '\033') { pvim_mode = 0; }
            else if (input > 0) pvim_buffer = picos_str_addch(pvim_buffer, input);
            break;
        }
        case 2: {
            graphics_draw_string_inv(renderer, "COMMAND", 0, 56);
            printf("PVIM Commands aren't yet added\n");
            break;
        }
    }
}
