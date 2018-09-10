#pragma once

#include "lisp/typedef.h"

enum {
    TYPE_INT = 1,
    TYPE_CONS,
    TYPE_SYMBOL,
    TYPE_STRING,
};

struct __object_t {
    __int type;
    union {
        // Int
        __int value;
        // Cons
        byte *ptr;
        // Symbol
        char *name;
        // String
        char *str;
    };
};

bool operator==(object_t a, object_t b);

bool operator!=(object_t a, object_t b);


/*
 * Null
 */

extern object_t nil;

bool null(object_t form);


/*
 * Int
 */

object_t make_int(__int value);

bool is_int(object_t form);

__int int_value(object_t form);


/*
 * Cons
 */

object_t make_cons(object_t car, object_t cdr);

bool is_cons(object_t form);

object_t car(object_t form);

object_t cdr(object_t form);


/*
 * Symbol
 */

object_t make_symbol(const char *name);

bool is_symbol(object_t form);

const char* symbol_name(object_t form);

/*
 * String
 */

object_t make_string(const char *str);

bool is_string(object_t form);

const char* string_str(object_t form);
