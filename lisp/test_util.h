#pragma once

#include "object.h"

bool operator==(object_t a, object_t b);

bool operator!=(object_t a, object_t b);

bool operator==(OPTIONAL(object_t) a, OPTIONAL(object_t) b);

bool operator!=(OPTIONAL(object_t) a, OPTIONAL(object_t) b);
