#pragma once

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

bool is_list(object_t object);

bool list_equal(object_t x, object_t y);

#ifdef __cplusplus
}
#endif
