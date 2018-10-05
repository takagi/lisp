#include "lisp/eval.h"

#include "lisp/assert.h"
#include "lisp/error.h"
#include "lisp/lexenv.h"
#include "lisp/symbol.h"


object_t eval_symbol(object_t form, object_t lenv) {
    lexenv_find_variable_result_t result;

    if (null(form))
        return nil;

    result = lexenv_find_variable(form, lenv);
    if (result.found)
        return result.value;
    else
        error("Variable not found.");
}

object_t eval_cons(object_t form, object_t lenv) {
    object_t name;

    name = car(form);

    if (name == intern("QUOTE"))
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
