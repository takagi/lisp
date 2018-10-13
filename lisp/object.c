#include "object.h"

#include <string.h>

#include "assert.h"
#include "error.h"
#include "memory.h"

bool eq(object_t a, object_t b) {
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

/*
 * Null
 */

object_t nil = {TYPE_SYMBOL, 0};

bool null(object_t form) {
    return form.type == TYPE_SYMBOL && form.name == 0;
}

/*
 * Int
 */

object_t make_int(__int value) {
    return (object_t){TYPE_INT, value};
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
    byte *ptr;

    ptr = alloc(sizeof(object_t) * 2);
    assert(ptr);

    *(object_t *)ptr = car;
    *(object_t *)(ptr + sizeof(object_t)) = cdr;

    return (object_t){TYPE_CONS, .ptr=ptr};
}

bool is_cons(object_t form) {
    return form.type == TYPE_CONS;
}

object_t car(object_t form) {
    if (form.type == TYPE_CONS)
        return *(object_t *)form.ptr;
    else if (null(form))
        return nil;
    else
        error("Not of type LIST.");
}

object_t cdr(object_t form) {
    if (form.type == TYPE_CONS)
        return *(object_t *)(form.ptr + sizeof(object_t));
    else if (null(form))
        return nil;
    else
        error("Not of type LIST.");
}

object_t rplaca(object_t cons, object_t obj) {
    assert(cons.type == TYPE_CONS);
    *(object_t *)cons.ptr = obj;
    return cons;
}

object_t rplacd(object_t cons, object_t obj) {
    assert(cons.type == TYPE_CONS);
    *(object_t *)(cons.ptr + sizeof(object_t)) = obj;
    return cons;
}

/*
 * Symbol
 */

object_t make_symbol(const char* name) {
    object_t result;
    char *ptr;

    ptr = (char *)alloc(strlen(name) + 1);
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
        return null(form) ? "NIL" : form.name;
    else
        error("Invalid type.");
}

/*
 * String
 */

object_t make_string(const char* str) {
    char *ptr;

    ptr = (char *)alloc(strlen(str) + 1);
    assert(ptr);
    strcpy(ptr, str);

    return (object_t){TYPE_STRING, .str=ptr};
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
