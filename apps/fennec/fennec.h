#ifndef PVIM_H
#define PVIM_H

#include "../core/application.h"
#include "../core/picos.h"

#include "../os/util/picos_str.h"
#include "../os/util/picos_buffer.h"
#include "../os/util/picos_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct application* fennec_new(void);

void fennec_begin(void);
void fennec_update(void);

// -- private functions --
void fennec_draw_cursor(void);
void fennec_handle_arrows(int v);
void fennec_draw_buffer(void);

#endif
