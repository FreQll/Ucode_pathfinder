#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long base = 1;
    unsigned long result = 0;

    if (!hex) return 0;

    for (int i = mx_strlen(hex) - 1; i >= 0; i--) {
        if (hex[i] >= 48 && hex[i] <= 57) {
            result += (hex[i] - 48) * base;
            base *= 16;
        }
        else if (hex[i] >= 65 && hex[i] <= 90) {
            result += (hex[i] - 55) * base;
            base *= 16;
        }
        else if (hex[i] >= 97 && hex[i] <= 122) {
            result += (hex[i] - 87) * base;
            base *= 16;
        }
    }
    return result;
}
