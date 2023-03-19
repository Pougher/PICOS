#include "application.h"

void application_free(struct application* app) {
    // frees an app struct allocated on the heap
    free(app->name);
    free(app->description);
    free(app->icon);
    free(app);
}
