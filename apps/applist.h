#ifndef APPLIST_H
#define APPLIST_H

#include "applications.h"
#include "../core/application.h"

#define APP_NUM 10

extern struct application* (*APP_LIST[APP_NUM])(void);

#endif
