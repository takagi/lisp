#include "list.h"

bool is_list(object_t object) {
    return is_cons(object) || null(object);
}

bool list_equal(object_t x, object_t y) {
    if (null(x) && null(y))
        return true;

    if (!is_cons(x))
        return false;

    if (!is_cons(y))
        return false;

    if (!eq(car(x), car(y)))
        return false;

    return list_equal(cdr(x), cdr(y));
}
