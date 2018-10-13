#include "memory.h"

#include "assert.h"
#include "error.h"

#define MEMORY_SIZE 32768

byte memory[MEMORY_SIZE];

size_t align(size_t ptr) {
    return (((ptr - 1) / 4) + 1) * 4;
}

byte* alloc(size_t size) {
    static byte *ptr = NULL;
    byte *ret;

    if (!ptr)
        ptr = (byte *)align((size_t)memory);

    size = align(size);
    assert(size % 4 == 0);

    ret = ptr;
    ptr += align(size);
    if (ptr - memory >= MEMORY_SIZE)
        error("Memory exhausted.");

    return ret;
}

void __free(byte *ptr) {
    return;
}
