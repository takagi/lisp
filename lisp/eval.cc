#include "lisp/eval.h"

#include "lisp/assert.h"
#include "lisp/error.h"
#include "lisp/lexenv.h"


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

object_t __eval(object_t form, object_t lenv) {
    if (is_symbol(form))
        return eval_symbol(form, lenv);

    if (is_cons(form))
        assert(false);

    return form;
}

object_t eval(object_t form) {
    return __eval(form, empty_lexenv());
}
