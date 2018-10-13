#include "serial.h"

#include <Arduino.h>

size_t serial_print_str(const char str[]) {
    return Serial.print(str);
}

size_t serial_print_int(int n) {
    return Serial.print(n);
}

size_t serial_print_long(long n) {
    return Serial.print(n);
}

size_t serial_println() {
    return Serial.println();
}

size_t serial_println_str(const char str[]) {
    return Serial.println(str);
}

size_t serial_println_err(const char str[]) {
    return Serial.println(str);
}
