#include "eval.h"

#include "assert.h"
#include "error.h"
#include "lexenv.h"
#include "symbol.h"

object_t eval_symbol(object_t form, object_t lenv) {
    OPTIONAL(object_t) var;

    if (null(form))
        return nil;

    var = lexenv_find_variable(form, lenv);
    if (var.has_value)
        return var.value;
    else
        error("Variable not found.");
}

object_t eval_cons(object_t form, object_t lenv) {
    object_t name;

    name = car(form);

    if (eq(name, intern("QUOTE")))
        return car(cdr(form));

    assert(false);
}

object_t __eval(object_t form, object_t lenv) {
    if (is_symbol(form))
        return eval_symbol(form, lenv);

    if (is_cons(form))
        return eval_cons(form, lenv);

    return form;
}

object_t eval(object_t form) {
    return __eval(form, empty_lexenv());
}
