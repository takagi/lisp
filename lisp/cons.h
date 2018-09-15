#pragma once

#include "lisp/object.h"


object_t cons(object_t se1, object_t se2);

object_t acons(object_t key, object_t datum, object_t alist);
