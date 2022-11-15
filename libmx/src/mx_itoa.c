#include "../inc/libmx.h"

char *mx_itoa(long long number) {
    char *result = NULL;

    if (number == 0) {
        result = mx_strnew(1);
        result[0] = '0';
        return result;
    }
    int length = 0;
    long long temp = number;
    
    if (temp < 0) {
        length++;
        temp *= -1;
    }
    while (temp != 0) {
        temp /= 10;
        length++;
    }
    result = mx_strnew(length);
    if (number < 0) {
        result[0] = '-';
        number *= -1;
    }
    result[length--] = '\0';
    while ((number != 0 && length >= 0) && result[length] != '-') {
        result[length--] = (number % 10) + '0';
        number /= 10;
    }
    return result;
}
