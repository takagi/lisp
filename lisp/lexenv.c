#include "lexenv.h"

#include "assert.h"
#include "cons.h"
#include "error.h"

object_t empty_lexenv() {
    return cons(nil, nil);
}

object_t lexenv_new_frame(object_t lenv) {
    return cons(nil, lenv);
}

object_t lexenv_add_variable(object_t symbol, object_t value, object_t lenv) {
    assert(is_symbol(symbol));
    object_t frame = car(lenv);
    object_t rest = cdr(lenv);
    return cons(acons(symbol, value, frame), rest);
}

// lexenv_add_symbol_macro

// lexenv_add_function

// lexenv_add_macro

// lexenv_add_block_tag

// lexenv_add_go_tag

// lexenv_add_declaration

OPTIONAL(object_t) lexenv_find_variable(object_t symbol, object_t lenv) {
    object_t frame = car(lenv);
    object_t pair;

    if (!is_symbol(symbol))
        error("Invalid type.");

    while (true) {
        pair = car(frame);

        if (null(pair))
            return (OPTIONAL(object_t)){false, nil};

        if (eq(symbol, car(pair)))
            return (OPTIONAL(object_t)){true, cdr(pair)};

        frame = cdr(frame);
    }
}

// lexenv_find_function

// lexenv_find_block_tag

// lexenv_find_go_tag

// lexenv_declarations
