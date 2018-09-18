#include "lisp/eval.h"

#include "lisp/error.h"
#include "lisp/lexenv.h"


object_t eval_symbol(object_t form, object_t lenv) {
    lexenv_find_variable_result_t result = lexenv_find_variable(form, lenv);
    if (result.found)
        return result.value;
    else
        error("Variable not found.");
}
