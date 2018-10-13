#pragma once

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t serial_print_str(const char str[]);
size_t serial_print_int(int n);
size_t serial_print_long(long n);

size_t serial_println(void);
size_t serial_println_str(const char str[]);
size_t serial_println_err(const char str[]);

#ifdef __cplusplus
}
#endif
