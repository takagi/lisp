#pragma once

#include <stdlib.h>

#include "typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

byte* alloc(size_t size);

void __free(byte *ptr);

#ifdef __cplusplus
}
#endif
