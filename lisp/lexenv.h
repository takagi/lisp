#pragma once

#include "lisp/object.h"


object_t empty_lexenv();

// lexenv_new_frame

object_t lexenv_add_variable(object_t symbol, object_t value, object_t lenv);

// lexenv_add_symbol_macro

// lexenv_add_function

// lexenv_add_macro

// lexenv_add_block_tag

// lexenv_add_go_tag

// lexenv_add_declaration

// lexenv_find_variable

// lexenv_find_function

// lexenv_find_block_tag

// lexenv_find_go_tag

// lexenv_declarations
