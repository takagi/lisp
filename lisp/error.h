#pragma once

#include <stdlib.h>

#include "serial.h"

#define error(__e)                              \
    do {                                        \
        serial_println_err(__e);                \
        exit(-1);                               \
    } while(0)
