#include "lisp/object.h"

#include <cstring>

#include "lisp/assert.h"
#include "lisp/memory.h"


bool operator==(object_t a, object_t b) {
    return memcmp(&a, &b, sizeof(object_t)) == 0;
}

bool operator!=(object_t a, object_t b) {
    return !(a == b);
}


/*
 * Null
 */

object_t nil = {TYPE_SYMBOL, 0};

bool null(object_t form) {
    return form == nil;
}


/*
 * Int
 */

object_t make_int(__int value) {
    return {TYPE_INT, value};
}

bool is_int(object_t form) {
    return form.type == TYPE_INT;
}

__int int_value(object_t form) {
    assert(form.type == TYPE_INT);
    return form.value;
}


/*
 * Cons
 */

object_t make_cons(object_t car, object_t cdr) {
    byte *ptr = alloc(sizeof(object_t) * 2);
    assert(ptr);

    *reinterpret_cast<object_t *>(ptr) = car;
    *reinterpret_cast<object_t *>(ptr + sizeof(object_t)) = cdr;

    return {TYPE_CONS, .ptr=ptr};
}

bool is_cons(object_t form) {
    return form.type == TYPE_CONS;
}

object_t car(object_t form) {
    assert(form.type == TYPE_CONS || form == nil);
    return form.type == TYPE_CONS
        ? *reinterpret_cast<object_t *>(form.ptr)
        : nil;
}

object_t cdr(object_t form) {
    assert(form.type == TYPE_CONS || form == nil);
    return form.type == TYPE_CONS
        ? *reinterpret_cast<object_t *>(form.ptr + sizeof(object_t))
        : nil;
}


/*
 * Symbol
 */

object_t make_symbol(const char* name) {
    auto ptr = reinterpret_cast<char *>(alloc(strlen(name) + 1));
    assert(ptr);
    strcpy(ptr, name);

    return {TYPE_SYMBOL, .name=ptr};
}

bool is_symbol(object_t form) {
    return form.type == TYPE_SYMBOL;
}

const char* symbol_name(object_t form) {
    assert(form.type == TYPE_SYMBOL);
    return form == nil ? "NIL" : form.name;
}
