#include "test_util.h"

bool operator==(object_t a, object_t b) {
    return eq(a, b);
}

bool operator!=(object_t a, object_t b) {
    return !(a == b);
}

bool operator==(OPTIONAL(object_t) a, OPTIONAL(object_t) b) {
    return a.has_value == b.has_value && a.value == b.value;
}

bool operator!=(OPTIONAL(object_t) a, OPTIONAL(object_t) b) {
    return !(a == b);
}
