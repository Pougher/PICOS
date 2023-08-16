#ifndef PVIM_H
#define PVIM_H

#include "../core/application.h"
#include "../core/picos.h"

#include "../os/util/picos_str.h"
#include "../os/util/picos_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct application* pvim_new(void);

void pvim_begin(void);
void pvim_update(void);

// -- private functions --
void pvim_draw_cursor(void);
void pvim_handle_arrows(int v);
void pvim_draw_buffer(void);

#endif
