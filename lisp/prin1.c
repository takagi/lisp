#include "prin1.h"

#include "serial.h"

void prin1(object_t x) {
    switch(x.type) {
    case TYPE_INT:
        serial_print_long((long)x.value);
        return;
    case TYPE_CONS:
        serial_print_str("(");
        prin1(car(x));
        x = cdr(x);
        while (true) {
            if (null(x))
                break;

            if (!is_cons(x)) {
                serial_print_str(" . ");
                prin1(x);
                break;
            }

            serial_print_str(" ");
            prin1(car(x));
            x = cdr(x);
        }
        serial_print_str(")");
        return;
    case TYPE_SYMBOL:
        // TODO: Fix to print symbols that contain non-constituent characters
        if (null(x))
            serial_print_str("()");
        else
            serial_print_str(x.name);
        return;
    case TYPE_STRING:
        serial_print_str("\"");
        serial_print_str(x.str);
        serial_print_str("\"");
        return;
    }
}
