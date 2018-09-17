#include "lisp/lexenv.h"

#include "lisp/assert.h"
#include "lisp/cons.h"


object_t empty_lexenv() {
    return cons(nil, nil);
}

object_t lexenv_add_variable(object_t symbol, object_t value, object_t lenv) {
    assert(is_symbol(symbol));
    object_t frame = car(lenv);
    object_t rest = cdr(lenv);
    return cons(acons(symbol, value, frame), rest);
}
