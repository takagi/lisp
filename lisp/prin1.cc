#include "lisp/prin1.h"

#include "lisp/printf.h"


void prin1(object_t x) {
    object_t y;

    switch(x.type) {
    case TYPE_INT:
        __printf("%td", x.value);
        return;
    case TYPE_CONS:
        y = x;
        __printf("(");
        prin1(car(y));
        while (true) {
            y = cdr(y);
            if (y == nil)
                break;
            else if (y.type == TYPE_CONS) {
                __printf(" ");
                prin1(car(y));
                continue;
            } else {
                __printf(" . ");
                prin1(y);
                break;
            }
        }
        __printf(")");
        return;
    case TYPE_SYMBOL:
        // TODO: Fix to print symbols that contain non-constituent characters
        __printf("%s", x.name);
        return;
    case TYPE_STRING:
        __printf("\"%s\"", x.str);
        return;
    }
}
