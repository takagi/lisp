#pragma once

#include "object.h"
#include "optional.h"

#ifdef __cplusplus
extern "C" {
#endif

object_t empty_lexenv();

object_t lexenv_new_frame(object_t lenv);

object_t lexenv_add_variable(object_t symbol, object_t value, object_t lenv);

// lexenv_add_symbol_macro

// lexenv_add_function

// lexenv_add_macro

// lexenv_add_block_tag

// lexenv_add_go_tag

// lexenv_add_declaration

OPTIONAL(object_t) lexenv_find_variable(object_t symbol, object_t lenv);

// lexenv_find_function

// lexenv_find_block_tag

// lexenv_find_go_tag

// lexenv_declarations

#ifdef __cplusplus
}
#endif
