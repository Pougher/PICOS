#include "applist.h"

struct application* (*APP_LIST[APP_NUM])(void) = {
    fennec_new,
    term_new,
    fennec_new,
    term_new,
    fennec_new,
    term_new,
    fennec_new,
    term_new,
    fennec_new,
    term_new,
};
