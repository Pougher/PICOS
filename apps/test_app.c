#include "test_app.h"

struct application* test_app_new(void) {
    struct application* test_app = malloc(sizeof(struct application));

    strcpy(test_app->name, "TEST APP");
    strcpy(test_app->description, "amonger");

    test_app->begin = test_app_begin;
    test_app->update = test_app_update;

    return test_app;
}

void test_app_begin(void) {
    printf("Begin called!\n");
}

void test_app_update(void) {
    graphics_draw_string(renderer, "Update Called!", 20, 20);
    if (keyboard->keys[(int)'a'] && keyboard->keys[(int)'b'])
        graphics_draw_string(renderer, "A+B pressed", 30, 20);
}
