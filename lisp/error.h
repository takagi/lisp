#pragma once

#include <cstdlib>
#include <cstdio>


#define error(__e...)         \
    do {                      \
        fprintf(stderr, __e); \
        exit(-1);             \
    } while(0)
