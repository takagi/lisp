#pragma once

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

object_t cons(object_t se1, object_t se2);

object_t acons(object_t key, object_t datum, object_t alist);

#ifdef __cplusplus
}
#endif
