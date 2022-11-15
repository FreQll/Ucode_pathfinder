#include "../inc/libmx.h"

char *mx_strcat(char *s1, const char *s2) {
    int length_s1 = mx_strlen(s1);
    int length_s2 = mx_strlen(s2);
    
    for (int i = 0; i < length_s2; i++) {
        s1[length_s1 + i] = s2[i];
    }
    s1[length_s1 + length_s2] = '\0';
    return s1;
}
