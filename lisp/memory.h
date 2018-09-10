#pragma once

#include <cstdlib>

#include "lisp/typedef.h"

byte* alloc(size_t size);

void free(byte *ptr);
