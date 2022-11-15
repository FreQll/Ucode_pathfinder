char *mx_strcpy(char *dst, const char *src) {
    int i = 0;
    for (; *src; i++) *dst++ = *src++;

    for (; *dst; i++) *dst++ = 0;

    dst -= i;
    return dst;
}
