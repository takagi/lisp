#include "lisp/memory.h"

#include "lisp/assert.h"

constexpr int memory_size = 32768;

byte memory[memory_size];

byte* alloc(size_t size) {
    static byte *ptr = memory;
    byte *ret;

    // Allocate memory region per 4 bytes for keeping off the alignment
    // exception.
    size = ((size - 1) / 4 + 1) * 4;
    assert(size % 4 == 0);

    if (ptr - memory + size >= memory_size) {
        // println("Memory exhausted.");
        return 0;
    }

    ret = ptr;
    ptr += size;
    return ret;
}

void free(byte *ptr) {
    return;
}
