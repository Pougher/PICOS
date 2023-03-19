#ifndef TEST_APP
#define TEST_APP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../core/application.h"
#include "../core/picos.h"

struct application* test_app_new(void);

void test_app_begin(void);
void test_app_update(void);

#endif
