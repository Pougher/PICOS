#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <stdlib.h>

// every application has a name, a description
// and an icon that is a bitmap with a resolution of 32x19 pixels.

struct application {
    char name[12];
    char description[40];
    char icon[32][19];
    void (*begin)(void);
    void (*update)(void);
};

void application_free(struct application* app);

#endif
