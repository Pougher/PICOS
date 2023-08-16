#include "picos_str.h"

_picos_str picos_str_new(void) {
    _picos_str new_str = malloc(sizeof(picos_str_t));
    new_str->str = NULL;
    new_str->len = 0;

    return new_str;
}

void picos_str_set(_picos_str str, char* s, int len) {
    str->str = realloc(str->str, len + 1);
    strncpy(str->str, s, len);
    str->str[len] = 0;
    str->len = len;
}

void picos_str_append(_picos_str str, char* s, int len) {
    str->len = str->len + len;
    str->str = realloc(str->str, str->len + 1);
    strncat(str->str, s, len);
    str->str[str->len] = 0;
}

void picos_str_addch(_picos_str str, char c) {
    str->len++;
    str->str = realloc(str->str, str->len + 1);
    str->str[str->len - 1] = c;
    str->str[str->len] = 0;
}

void picos_str_clear(_picos_str str) {
    str->len = 0;
    str->str = realloc(str->str, str->len + 1);
    str->str[str->len] = 0;
}

void picos_str_free(_picos_str str) {
    free(str->str);
    free(str);
}

void picos_str_insert(_picos_str str1, char* str2, int pos) {
    size_t l1 = str1->len;
    str1->len++;
    str1->str = realloc(str1->str, str1->len + 1);
    size_t l2 = strlen(str2);

    if (pos <  0) pos = 0;
    if (pos > (int)l1) pos = l1;

    char *p  = str1->str + pos;
    memmove(p + l2, p, l1 - pos);
    memcpy(p, str2,  l2);
    str1->str[str1->len] = 0;
}

void picos_str_delete(_picos_str str, int index) {
    memmove(&str->str[index], &str->str[index + 1], str->len - index);
    str->len--;
}
