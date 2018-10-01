#include "lisp/object.h"

#include <cstring>

#include "lisp/assert.h"
#include "lisp/error.h"
#include "lisp/memory.h"


bool operator==(object_t a, object_t b) {
    if (a.type != b.type) {
        return false;
    }

    switch(a.type) {
    case TYPE_INT:
        return a.value == b.value;
    case TYPE_CONS:
        return a.ptr == b.ptr;
    case TYPE_SYMBOL:
        return a.name == b.name;
    case TYPE_STRING:
        return strcmp(a.str, b.str) == 0;
    default:
        assert(false);
    }
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
    if (form.type == TYPE_INT)
        return form.value;
    else
        error("Invalid type.");
}


/*
 * Cons
 */

object_t make_cons(object_t car, object_t cdr) {
    object_t result;
    byte *ptr;

    ptr = alloc(sizeof(object_t) * 2);
    assert(ptr);

    *reinterpret_cast<object_t *>(ptr) = car;
    *reinterpret_cast<object_t *>(ptr + sizeof(object_t)) = cdr;

    result.type = TYPE_CONS;
    result.ptr = ptr;
    return result;
}

bool is_cons(object_t form) {
    return form.type == TYPE_CONS;
}

object_t car(object_t form) {
    if (form.type == TYPE_CONS)
        return *reinterpret_cast<object_t *>(form.ptr);
    else if (form == nil)
        return nil;
    else
        error("Not of type LIST.");
}

object_t cdr(object_t form) {
    if (form.type == TYPE_CONS)
        return *reinterpret_cast<object_t *>(form.ptr + sizeof(object_t));
    else if (form == nil)
        return nil;
    else
        error("Not of type LIST.");
}

object_t rplaca(object_t cons, object_t obj) {
    assert(cons.type == TYPE_CONS);
    *reinterpret_cast<object_t *>(cons.ptr) = obj;
    return cons;
}

object_t rplacd(object_t cons, object_t obj) {
    assert(cons.type == TYPE_CONS);
    *reinterpret_cast<object_t *>(cons.ptr + sizeof(object_t)) = obj;
    return cons;
}


/*
 * Symbol
 */

object_t make_symbol(const char* name) {
    object_t result;
    char *ptr;

    ptr = reinterpret_cast<char *>(alloc(strlen(name) + 1));
    assert(ptr);
    strcpy(ptr, name);

    result.type = TYPE_SYMBOL;
    result.name = ptr;
    return result;
}

bool is_symbol(object_t form) {
    return form.type == TYPE_SYMBOL;
}

const char* symbol_name(object_t form) {
    if (form.type == TYPE_SYMBOL)
        return form == nil ? "NIL" : form.name;
    else
        error("Invalid type.");
}


/*
 * String
 */

object_t make_string(const char* str) {
    object_t result;
    char *ptr;

    ptr = reinterpret_cast<char *>(alloc(strlen(str) + 1));
    assert(ptr);
    strcpy(ptr, str);

    result.type = TYPE_STRING;
    result.str = ptr;
    return result;
}

bool is_string(object_t form) {
    return form.type == TYPE_STRING;
}

const char* string_str(object_t form) {
    if (form.type == TYPE_STRING)
        return form.str;
    else
        error("Invalid type.");
}
