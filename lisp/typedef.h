#pragma once

#include <cstddef>

#ifndef ARDUINO
typedef unsigned char byte;
#endif  // ARDUINO

typedef ptrdiff_t __int;

#ifndef ARDUINO
struct __object_t;
#endif  // ARDUINO
typedef __object_t object_t;
