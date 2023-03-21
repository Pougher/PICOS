#include "pvim.h"

struct application* pvim_new(void) {
    struct application* pvim = malloc(sizeof(struct application));

    strcpy(pvim->name, "PVIM");
    strcpy(pvim->description, "Picos VIM Text Editor");

    pvim->begin = pvim_begin;
    pvim->update = pvim_update;

    return pvim;
}

void pvim_begin(void) {

}

void pvim_update(void) {
    graphics_draw_string_inv(renderer, "INSERT", 0, 56);
    graphics_draw_string(renderer, "file.txt", 50, 56);
    graphics_draw_line(renderer, 0, 55, 128, 55);
    graphics_draw_line(renderer, 0, 63, 128, 63);
}
