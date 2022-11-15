#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int i = 0;
    for (; i < len; i++) *dst++ = *src++;

    for (; *dst; i++) *dst++ = 0;

    dst -= i;
    return dst;
}
