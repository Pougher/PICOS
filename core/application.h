#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <stdlib.h>

// every application has a name, a description
// and an icon that is a bitmap with a resolution of 32x19 pixels.

#define APP_ICON_WIDTH 4 // 4 bytes
#define APP_ICON_HEIGHT 19

struct application {
    char name[12];
    char description[40];
    char** icon;
    void (*begin)(void);
    void (*update)(void);
};

void application_free(struct application* app);

#endif
