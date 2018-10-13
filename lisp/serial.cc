#include "serial.h"

#include <cstdio>

size_t serial_print_str(const char str[]) {
    return printf("%s", str);
}

size_t serial_print_int(int n) {
    return printf("%d", n);
}

size_t serial_print_long(long n) {
    return printf("%ld", n);
}

size_t serial_println() {
    return printf("\n");
}

size_t serial_println_str(const char str[]) {
    return printf("%s\n", str);
}

size_t serial_println_err(const char str[]) {
    return fprintf(stderr, "%s\n", str);
}
