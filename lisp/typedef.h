#pragma once

#include <cstddef>

#ifndef ARDUINO
typedef unsigned char byte;
#endif  // not ARDUINO

typedef ptrdiff_t __int;

#ifndef ARDUINO
struct __object_t;
struct __reader_macro_result_t;
#endif  // not ARDUINO

typedef __object_t object_t;
typedef __reader_macro_result_t reader_macro_result_t;
