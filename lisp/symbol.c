#include "symbol.h"

#include <string.h>

object_t __symbols = {TYPE_SYMBOL, 0};

object_t intern(const char* name) {
    object_t x = __symbols;

    while (true) {
        object_t y = car(x);
        if (strcmp(name, symbol_name(y)) == 0) {
            return y;
        }
        if (null(x)) {
            break;
        }
        x = cdr(x);
    }

    object_t symbol = make_symbol(name);
    __symbols = make_cons(symbol, __symbols);
    return symbol;
}
