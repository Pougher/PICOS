#include "fennec.h"

// probably some of the worst code I have ever written

static _picos_buffer fennec_buffer;
static _picos_buffer fennec_cur_line;
static _picos_str fennec_status_buffer;
static _picos_input fennec_cmd_buffer;
static _picos_input fennec_filename;
static int fennec_mode;
static int fennec_statusline_timeout;
static int fennec_buffer_window_begin;

static char* fennec_boot_screen = " FENNEC EDITOR\n"
                                "by Jobe Pougher\n\n";
static char* fennec_boot_help = ":q to exit\n"
                              ":o to open files";
static int fennec_render_boot = 1;

static struct { int x; int y; int true_y; } fennec_cursor;

struct application* fennec_new(void) {
    struct application* fennec = malloc(sizeof(struct application));

    strcpy(fennec->name, "FENNEC");
    strcpy(fennec->description, "Fennec Text Editor");

    fennec->begin = fennec_begin;
    fennec->update = fennec_update;


    return fennec;
}

void fennec_begin(void) {
    fennec_buffer = picos_buffer_new();

    fennec_cmd_buffer = picos_input_new();

    fennec_status_buffer = picos_str_new();
    picos_str_set(fennec_status_buffer, "", 0);

    fennec_filename = picos_input_new();
    picos_str_set(fennec_filename->text, "[NO NAME]", 9);

    // 0 = normal
    // 1 = insert
    // 2 = command
    fennec_mode = 0;
    fennec_statusline_timeout = 0;

    fennec_cursor.x = 0;
    fennec_cursor.y = 0;
    fennec_cursor.true_y = 0;
    fennec_cur_line = fennec_buffer;
    fennec_buffer_window_begin = 0;

    fennec_filename->draw_cursor = 0;
}

void fennec_draw_cursor(void) {
    char c[2] = { 0x11 + fennec_mode, '\0' };
    if (fennec_cursor.x < 20) {
        graphics_draw_string(renderer, c, (fennec_cursor.x % 20) * 6,
            fennec_cursor.y * 8);
    } else {
        if (fennec_cursor.x % 20 + 2 <= 20) {
            graphics_draw_string(renderer, c, (fennec_cursor.x % 20 + 2) * 6,
            fennec_cursor.y * 8);
        }
    }
}

void fennec_handle_arrows(int v) {
    switch(v) {
        case 181: {
            if (fennec_cur_line->last != NULL) {
                if (fennec_cursor.y > 0) fennec_cursor.y--;
                else {
                    if (fennec_buffer_window_begin > 0)
                        fennec_buffer_window_begin--;
                    }
                fennec_cur_line = fennec_cur_line->last;
                fennec_cursor.x = fennec_cur_line->v->len;
                fennec_cursor.true_y--;
            }
            break;
        }
        case 182: {
            if (fennec_cur_line->next != NULL) {
                if (fennec_cursor.y < 6) fennec_cursor.y++;
                else {
                    fennec_buffer_window_begin += 1;
                }
                fennec_cur_line = fennec_cur_line->next;
                fennec_cursor.x = fennec_cur_line->v->len;
                fennec_cursor.true_y++;
            }
            break;
        }
        case 180: {
            if (fennec_cursor.x > 0) fennec_cursor.x--;
            break;
        }
        case 183: {
            if (fennec_cursor.x < (int)fennec_cur_line->v->len) {
                fennec_cursor.x++;
            }
            break;
        }
    }
}

void fennec_draw_buffer(void) {
    int i = fennec_buffer_window_begin;
    _picos_buffer pos = fennec_buffer;
    for (int x = 0; x < i; x++) pos = pos->next;
    while (i < fennec_buffer_window_begin + 7 && pos != NULL) {
        int string_len = pos->v->len;
        if (string_len >= 20) {
            int lower_bound = (string_len / 20) * 20 - 1;
            char buffer[22] = { 0 };

            if (pos == fennec_cur_line) {
                int offset = (fennec_cursor.x / 20) * 20;
                if (offset > 0) offset -= 1;
                strncpy(buffer, pos->v->str + offset, 20);
            } else {
                strncpy(buffer, pos->v->str + lower_bound,
                    20);
            }

            graphics_draw_string(renderer, buffer, 6,
                8 * (i - fennec_buffer_window_begin));
            graphics_draw_string(renderer, "$", 0, 8 * (i - fennec_buffer_window_begin));
        } else {
            graphics_draw_string(renderer, pos->v->str, 0, 8 * (i - fennec_buffer_window_begin));
        }
        pos = pos->next;
        i++;
    }
}

void fennec_update(void) {
    fennec_draw_buffer();
    int input = keyboard_read(keyboard);

    if (fennec_render_boot) {
        graphics_draw_string(renderer, fennec_boot_screen, 18, 8);
        graphics_draw_string(renderer, fennec_boot_help, 6, 32);
        if (input > 0 && input < 128) fennec_render_boot = 0;
    }

    switch(fennec_mode) {
        case 0: {
            graphics_draw_string_inv(renderer, "NORMAL", 0, 56);
            if (input == 'i') fennec_mode = 1;
            if (input == ';') fennec_mode = 2;
            fennec_draw_cursor();
            fennec_handle_arrows(input);
            break;
        }
        case 1: {
            graphics_draw_string_inv(renderer, "INSERT", 0, 56);
            if (input == '\033') { fennec_mode = 0; return; }
            if (input == 0x08) {
                if (fennec_cursor.x > 0) {
                    fennec_cursor.x--;
                    picos_str_delete(fennec_cur_line->v, fennec_cursor.x);
                } else if (fennec_cur_line->last != NULL) {
                    // delete the whole line
                    _picos_buffer last = fennec_cur_line->last;
                    _picos_buffer next = fennec_cur_line->next;
                    if (next != NULL) {
                        next->last = last;
                    }
                    last->next = next;
                    if (fennec_cur_line == fennec_buffer->end) fennec_buffer->end = last;
                    picos_str_free(fennec_cur_line->v);
                    free(fennec_cur_line);
                    fennec_cur_line = last;
                    if (fennec_cursor.y == 0) {
                        fennec_buffer_window_begin--;
                    } else {
                        fennec_cursor.y--;
                    }
                    fennec_cursor.true_y--;
                    fennec_cursor.x = last->v->len;
                }
            } else if (input == 0x0d) {
                if (fennec_cur_line == fennec_buffer->end) {
                    picos_buffer_newline(fennec_buffer);
                    fennec_cur_line = fennec_buffer->end;
                } else {
                    _picos_buffer inserted = picos_buffer_insert(fennec_buffer,
                        fennec_cursor.true_y);
                    fennec_cur_line = inserted;
                }
                fennec_cursor.y++;
                fennec_cursor.true_y++;
                if (fennec_cursor.y > 6) {
                    fennec_buffer_window_begin++;
                    fennec_cursor.y = 6;
                }
                fennec_cursor.x = 0;
            }
            else if (input > 0 && input < 128) {
                if (fennec_cursor.x == (int)fennec_cur_line->v->len) {
                    picos_str_addch(fennec_cur_line->v, input);
                } else {
                    char v[2] = { input, 0 };
                    picos_str_insert(fennec_cur_line->v, v,
                        fennec_cursor.x);
                }
                fennec_cursor.x++;
            }
            fennec_draw_cursor();
            fennec_handle_arrows(input);
            break;
        }
        case 2: {
            graphics_draw_string_inv(renderer, "COMMAND", 0, 56);
            graphics_draw_string(renderer, ":", 44, 55);
            picos_input_render(fennec_cmd_buffer, renderer, 48, 55, 12);
            if (input == '\033') {
                picos_input_reset(fennec_cmd_buffer);
                fennec_mode = 0;
                return;
            }
            if (input == 0x0d) {
                fennec_mode = 0;
                char* cmd = strtok(fennec_cmd_buffer->text->str, " ");

                if (strcmp(cmd, "q") == 0) {
                    picos_input_free(fennec_cmd_buffer);
                    picos_input_free(fennec_filename);
                    picos_buffer_free(fennec_buffer);
                    picos_str_free(fennec_status_buffer);

                    menu_exit_app(menu);
                    return;
                } else if (strcmp(cmd, "e") == 0) {
                    cmd = strtok(NULL, " ");
                    if (cmd == NULL) {
                        picos_str_set(fennec_status_buffer, "E <FILE>", 8);
                        fennec_statusline_timeout = 60;
                    } else {
                        picos_str_set(fennec_filename->text, cmd, strlen(cmd));
                    }
                } else if (strcmp(cmd, "o") == 0) {
                    cmd = strtok(NULL, " ");
                    if (cmd == NULL) {
                        picos_str_set(fennec_status_buffer, "O <FILE>", 8);
                        fennec_statusline_timeout = 60;
                    } else {
                        FILE* fp;
                        char* line = NULL;
                        size_t len = 0;
                        ssize_t read;

                        fp = fopen(cmd, "r");
                        if (fp == NULL) {
                            picos_str_set(fennec_status_buffer, "NOT EXIST", 10);
                            fennec_statusline_timeout = 60;
                            fclose(fp);
                            picos_input_reset(fennec_cmd_buffer);
                            return;
                        }
                        picos_buffer_free(fennec_buffer);
                        fennec_cursor.x = 0;
                        fennec_cursor.y = 0;
                        fennec_cursor.true_y = 0;
                        fennec_buffer = picos_buffer_new();
                        fennec_buffer_window_begin = 0;
                        fennec_cur_line = fennec_buffer;

                        while ((read = getline(&line, &len, fp)) != -1) {
                            line[read - 1] = '\0';
                            picos_str_set(fennec_buffer->end->v,
                                line, read - 1);
                            picos_buffer_newline(fennec_buffer);
                        }

                        fclose(fp);
                        picos_str_set(fennec_filename->text, cmd, strlen(cmd));
                        return;
                    }
                } else if (strcmp(cmd, "w") == 0) {
                    if (strcmp(fennec_filename->text->str, "[NO NAME]") == 0) {
                        picos_str_clear(fennec_status_buffer);
                        picos_str_set(fennec_status_buffer, "NO FILE", 7);
                        fennec_statusline_timeout = 60;
                    } else {
                        FILE* fptr = fopen(fennec_filename->text->str, "w");
                        if (!fptr) {
                            picos_str_clear(fennec_status_buffer);
                            picos_input_reset(fennec_cmd_buffer);
                            picos_str_set(fennec_status_buffer, "IOERROR", 7);
                            fennec_statusline_timeout = 60;
                            return;
                        }
                        _picos_buffer buf_cpy = fennec_buffer;
                        int len = 0;

                        while (buf_cpy != NULL) {
                            fprintf(fptr, "%s\n", buf_cpy->v->str);
                            len += buf_cpy->v->len;
                            buf_cpy = buf_cpy->next;
                        }
                        picos_str_clear(fennec_status_buffer);
                        char file_len[20] = { 0 };
                        sprintf(file_len, "%dB\n", len);
                        picos_str_set(fennec_status_buffer, file_len, strlen(file_len));

                        fennec_statusline_timeout = 60;
                        fclose(fptr);
                    }
                } else {
                    picos_str_clear(fennec_status_buffer);
                    picos_str_set(fennec_status_buffer, "INVALID CMD", 11);
                    fennec_statusline_timeout = 60;
                }
                picos_input_reset(fennec_cmd_buffer);
            }
            else if (input > 0 && input < 128) {
                picos_input_update(fennec_cmd_buffer, input);
            }
            break;
        }
    }
    if (fennec_mode != 2 && fennec_statusline_timeout == 0) {
        if (fennec_filename->text->len > 12) {
            graphics_draw_string(renderer,
                fennec_filename->text->str + (fennec_filename->text->len - 12),
                50, 56);
        } else {
            picos_input_render(fennec_filename, renderer, 50, 56, 12);
        }
    } else if (fennec_statusline_timeout) {
        graphics_draw_string(renderer, fennec_status_buffer->str, 50, 56);
    }

    if (fennec_statusline_timeout) fennec_statusline_timeout--;
    graphics_draw_line(renderer, 0, 55, 128, 55);
    graphics_draw_line(renderer, 0, 63, 128, 63);
}
