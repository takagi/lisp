#include "lisp/read.h"

#include <cstdio>

#include "lisp/error.h"
#include "lisp/symbol.h"


constexpr int read_buf_size = 256;

char read_buf[read_buf_size];

object_t __read(const char** pcode);

bool is_invalid_character(char x) {
    return false;
}

char read_char(const char** pcode) {
    if (**pcode == '\0') {
        return EOF;
    } else {
        return *(*pcode)++;
    }
}

void unread_char(const char** pcode) {
    (*pcode)--;
}

struct __reader_macro_result_t {
    bool has_value;
    object_t value;
};

reader_macro_result_t read_string(const char** pcode, char chr) {
    char x, y;
    char *buf = read_buf;

    while (true) {
        x = read_char(pcode);
        if (x == EOF) {
            error("End of file.");
        }

        if (x == chr) {
            return {true, make_string(read_buf)};
        }

        if (x == '\\') {
            y = read_char(pcode);
            if (y == EOF) {
                error("End of file.");
            }

            *buf++ = y;
            if (buf - read_buf == 256) {
                error("Too long string.");
            }
            continue;
        }

        *buf++ = x;
        if (buf - read_buf == 256) {
            error("Too long string.");
        }
    }
}

reader_macro_result_t read_quote(const char** pcode, char chr) {
    return {true, make_cons(intern("QUOTE"), make_cons(__read(pcode), nil))};
}

// read_list

reader_macro_result_t read_right_paren(const char** pcode) {
    error("Unmatched close parenthesis.");
}

reader_macro_result_t read_comment(const char** pcode) {
    char x;

    while (true) {
        x = read_char(pcode);
        if (x == EOF || x == '\n') {
            return {false, nil};
        }
    }
}

// read_token

object_t __read(const char** pcode) {
    return nil;
}

object_t read(const char* code) {
    return __read(&code);
}
