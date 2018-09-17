#pragma once

#include "lisp/object.h"


bool is_list(object_t object);

bool list_equal(object_t x, object_t y);
