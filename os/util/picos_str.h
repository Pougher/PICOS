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
void picos_str_set(_picos_str str, char* s, int len);

// appends a string to the end of a picos string
void picos_str_append(_picos_str str, char* s, int len);

// appends a character to the end of a picos string
void picos_str_addch(_picos_str str, char c);

// clears a picos string
void picos_str_clear(_picos_str str);

// frees the picos string
void picos_str_free(_picos_str str);

// inserts a string at a specific index
void picos_str_insert(_picos_str str1, char* str2, int pos);

// deletes a character in a specific position
void picos_str_delete(_picos_str str1, int index);

#endif
