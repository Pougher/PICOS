#include "picos_str.h"

_picos_str picos_str_new(void) {
    _picos_str new_str = malloc(sizeof(picos_str_t));
    new_str->str = NULL;
    new_str->len = 0;

    return new_str;
}

_picos_str picos_str_set(_picos_str str, char* s, int len) {
    str->str = realloc(str->str, len + 1);
    strncpy(str->str, s, len);
    str->str[len] = 0;
    str->len = len;

    return str;
}

_picos_str picos_str_append(_picos_str str, char* s, int len) {
    str->len = str->len + len;
    str->str = realloc(str->str, str->len + 1);
    strncat(str->str, s, len);
    str->str[str->len] = 0;

    return str;
}

_picos_str picos_str_addch(_picos_str str, char c) {
    str->len = str->len + 1;
    str->str = realloc(str->str, str->len + 1);
    str->str[str->len - 1] = c;
    str->str[str->len] = 0;

    return str;
}

void picos_str_free(_picos_str str) {
    free(str->str);
    free(str);
}
