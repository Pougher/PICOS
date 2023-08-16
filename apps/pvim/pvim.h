#ifndef PVIM_H
#define PVIM_H

#include "../core/application.h"
#include "../core/picos.h"

#include "../os/util/picos_str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct application* pvim_new(void);

void pvim_begin(void);
void pvim_update(void);

#endif
