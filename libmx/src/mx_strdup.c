#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    char *copy = mx_strnew(mx_strlen(str) + 1);
    mx_strcpy(copy, str);
    return copy;
}
