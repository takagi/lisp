#include "lisp/cons.h"


object_t cons(object_t se1, object_t se2) {
    return make_cons(se1, se2);
}

object_t acons(object_t key, object_t datum, object_t alist) {
    return cons(cons(key, datum), alist);
}
