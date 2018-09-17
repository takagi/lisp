#include "lisp/list.h"


bool is_list(object_t object) {
    return is_cons(object) || null(object);
}

bool list_equal(object_t x, object_t y) {
    object_t x0, y0;

    if (null(x) && null(y))
        return true;

    if (!is_cons(x))
        return false;

    if (!is_cons(y))
        return false;

    x0 = car(x);
    y0 = car(y);
    if (x0 != y0)
        return false;

    return list_equal(cdr(x), cdr(y));
}
