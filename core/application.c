#include "application.h"

void application_free(struct application* app) {
    // frees an app struct allocated on the heap
    // free the 2d array icon
    for (int i = 0; i < APP_ICON_HEIGHT; i++) {
        free(app->icon[i]);
    }
    free(app->icon);
    free(app);
}
