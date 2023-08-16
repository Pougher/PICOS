#ifndef UTIL_PICOS_STR_H
#define UTIL_PICOS_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* str;
    size_t len;
} picos_str_t;

#define _picos_str picos_str_t*

// creates a new picos string
_picos_str picos_str_new(void);

// sets the picos string to the specified char*
_picos_str picos_str_set(_picos_str str, char* s, int len);

// appends a string to the end of a picos string
_picos_str picos_str_append(_picos_str str, char* s, int len);

// appends a character to the end of a picos string
_picos_str picos_str_addch(_picos_str str, char c);

// frees the picos string
void picos_str_free(_picos_str str);

#endif