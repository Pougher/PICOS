#include "applist.h"

struct application* (*APP_LIST[APP_NUM])(void) = {
    pvim_new,
};
