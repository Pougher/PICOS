#ifndef APPLICATION_H
#define APPLICATION_H

struct application {
    char* name;
    void (*entry_point)(void);
};

#endif
