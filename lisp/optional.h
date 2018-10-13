#pragma once

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)

#define OPTIONAL(T) \
    CONCAT(optional_, T)

#define DEFINE_OPTIONAL(T) \
    typedef struct { \
        bool has_value; \
        T value; \
    } OPTIONAL(T);
