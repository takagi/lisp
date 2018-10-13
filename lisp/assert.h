#pragma once

#include <stdlib.h>

#include "serial.h"

#define assert(__e)                                     \
    do {                                                \
        if (!(__e)) {                                   \
            serial_println();                           \
            serial_print_str(__FILE__);                 \
            serial_print_str(":");                      \
            serial_print_int(__LINE__);                 \
            serial_print_str(" Assertion failed: ");    \
            serial_println_str(#__e);                   \
            serial_println_str("Restart...");           \
            exit(-1);                                   \
        }                                               \
    } while (0)
