#include "lisp/prin1.h"

#include "lisp/printf.h"


void prin1(object_t x) {
    switch(x.type) {
    case TYPE_INT:
        __printf("%ld", static_cast<long>(x.value));
        return;
    case TYPE_CONS:
        __printf("(");
        prin1(car(x));
        x = cdr(x);
        while (true) {
            if (x == nil)
                break;

            if (!is_cons(x)) {
                __printf(" . ");
                prin1(x);
                break;
            }

            __printf(" ");
            prin1(car(x));
            x = cdr(x);
        }
        __printf(")");
        return;
    case TYPE_SYMBOL:
        // TODO: Fix to print symbols that contain non-constituent characters
        if (x == nil)
            __printf("()");
        else
            __printf("%s", x.name);
        return;
    case TYPE_STRING:
        __printf("\"%s\"", x.str);
        return;
    }
}
