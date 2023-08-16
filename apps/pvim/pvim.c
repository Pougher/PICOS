#include "pvim.h"

// probably some of the worst code I have ever written

static _picos_buffer pvim_buffer;
_picos_buffer pvim_cur_line;
_picos_str pvim_cmd_buffer;
_picos_str pvim_status_buffer;
_picos_str pvim_filename;
int pvim_mode;
int pvim_statusline_timeout;
int pvim_buffer_window_begin;

struct { int x; int y; } pvim_cursor;

struct application* pvim_new(void) {
    struct application* pvim = malloc(sizeof(struct application));

    strcpy(pvim->name, "FENNEC");
    strcpy(pvim->description, "Fennec Text Editor");

    pvim->begin = pvim_begin;
    pvim->update = pvim_update;


    return pvim;
}

void pvim_begin(void) {
    pvim_buffer = picos_buffer_new();

    pvim_cmd_buffer = picos_str_new();
    picos_str_set(pvim_cmd_buffer, "", 0);

    pvim_status_buffer = picos_str_new();
    picos_str_set(pvim_status_buffer, "", 0);

    pvim_filename = picos_str_new();
    picos_str_set(pvim_filename, "[NO NAME]", 9);

    // 0 = normal
    // 1 = insert
    // 2 = command
    pvim_mode = 0;
    pvim_statusline_timeout = 0;

    pvim_cursor.x = 0;
    pvim_cursor.y = 0;
    pvim_cur_line = pvim_buffer;
    pvim_buffer_window_begin = 0;
}

void pvim_draw_cursor(void) {
    graphics_draw_string_inv(renderer, " ", (pvim_cursor.x) * 6,
        pvim_cursor.y * 8);
}

void pvim_handle_arrows(int v) {
    switch(v) {
        case 181: {
            pvim_cursor.y--;
            pvim_cur_line = pvim_cur_line->last;
            break;
        }
        case 182: {
            pvim_cursor.y++;
            pvim_cur_line = pvim_cur_line->next;
            break;
        }
        case 180: {
            pvim_cursor.x--;
            break;
        }
        case 183: {
            pvim_cursor.x++;
            break;
        }
    }
}

void pvim_draw_buffer(void) {
    int i = pvim_buffer_window_begin;
    _picos_buffer pos = pvim_buffer;
    while (i < pvim_buffer_window_begin + 10 && pos != NULL) {
        graphics_draw_string(renderer, pos->v->str, 0, 8 * i);
        pos = pos->next;
        i++;
    }
}

void pvim_update(void) {
    pvim_draw_buffer();
    int input = keyboard_read(keyboard);
    printf("%d\n", input);

    switch(pvim_mode) {
        case 0: {
            graphics_draw_string_inv(renderer, "NORMAL", 0, 56);
            if (input == 'i') pvim_mode = 1;
            if (input == ';') pvim_mode = 2;
            pvim_draw_cursor();
            pvim_handle_arrows(input);
            break;
        }
        case 1: {
            graphics_draw_string_inv(renderer, "INSERT", 0, 56);
            if (input == '\033') { pvim_mode = 0; }
            else if (input == 0x0d) {
                if (pvim_cur_line == pvim_buffer->end) {
                    printf("Done.\n");
                    picos_buffer_newline(pvim_buffer);
                    pvim_cur_line = pvim_buffer->end;
                } else {
                    _picos_buffer inserted = picos_buffer_insert(pvim_buffer,
                        pvim_cursor.y);
                    pvim_cur_line = inserted;
                }
                pvim_cursor.y++;
                pvim_cursor.x = 0;
            }
            else if (input > 0 && input < 128) {
                picos_str_addch(pvim_cur_line->v, input);
                pvim_cursor.x++;
            }
            pvim_draw_cursor();
            pvim_handle_arrows(input);
            break;
        }
        case 2: {
            graphics_draw_string_inv(renderer, "COMMAND", 0, 56);
            graphics_draw_string(renderer, ":", 44, 55);
            graphics_draw_string(renderer, pvim_cmd_buffer->str, 48, 55);
            if (input == '\033') { pvim_mode = 0; return; }
            if (input == 0x0d) {
                pvim_mode = 0;
                char* cmd = strtok(pvim_cmd_buffer->str, " ");

                if (strcmp(cmd, "q") == 0) {
                    picos_str_free(pvim_cmd_buffer);
                    picos_buffer_free(pvim_buffer);
                    picos_str_free(pvim_status_buffer);
                    picos_str_free(pvim_filename);

                    menu_exit_app(menu);
                    return;
                } else if (strcmp(cmd, "e") == 0) {
                    cmd = strtok(NULL, " ");
                    if (cmd == NULL) {
                        picos_str_clear(pvim_status_buffer);
                        picos_str_set(pvim_status_buffer, "E <FILE>", 8);
                        pvim_statusline_timeout = 60;
                    } else {
                        picos_str_set(pvim_filename, cmd, strlen(cmd));
                    }
                } else if (strcmp(cmd, "w") == 0) {
                    if (strcmp(pvim_filename->str, "[NO NAME]") == 0) {
                        picos_str_clear(pvim_status_buffer);
                        picos_str_set(pvim_status_buffer, "NO FILE", 7);
                        pvim_statusline_timeout = 60;
                    } else {
                        FILE* fptr = fopen(pvim_filename->str, "w");
                        if (!fptr) {
                            picos_str_clear(pvim_status_buffer);
                            picos_str_set(pvim_status_buffer, "IOERROR", 7);
                            pvim_statusline_timeout = 60;
                            return;
                        }
                        fprintf(fptr, "%s", pvim_cur_line->v->str);
                        picos_str_clear(pvim_status_buffer);
                        char file_len[20] = { 0 };
                        sprintf(file_len, "%zuB", pvim_cur_line->v->len);
                        picos_str_set(pvim_status_buffer, file_len, strlen(file_len));

                        pvim_statusline_timeout = 60;
                        fclose(fptr);
                    }
                } else {
                    picos_str_clear(pvim_status_buffer);
                    picos_str_set(pvim_status_buffer, "INVALID CMD", 11);
                    pvim_statusline_timeout = 60;
                }
                picos_str_clear(pvim_cmd_buffer);
            }
            else if (input > 0 && input < 128) picos_str_addch(pvim_cmd_buffer, input);
            break;
        }
    }
    if (pvim_mode != 2 && pvim_statusline_timeout == 0) {
        graphics_draw_string(renderer, pvim_filename->str, 50, 56);
    } else if (pvim_statusline_timeout) {
        graphics_draw_string(renderer, pvim_status_buffer->str, 50, 56);
    }

    if (pvim_statusline_timeout) pvim_statusline_timeout--;
    graphics_draw_line(renderer, 0, 55, 128, 55);
    graphics_draw_line(renderer, 0, 63, 128, 63);
}
