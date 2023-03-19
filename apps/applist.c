#include "applist.h"

struct application* (*APP_LIST[APP_NUM])(void) = {
    test_app_new,
};
