#include "lisp/read.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <cctype>

#include "lisp/assert.h"
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

typedef struct {
    bool has_value;
    object_t value;
} reader_macro_result_t;

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
            if (buf - read_buf == read_buf_size) {
                error("Too long string.");
            }
            continue;
        }

        *buf++ = x;
        if (buf - read_buf == read_buf_size) {
            error("Too long string.");
        }
    }
}

reader_macro_result_t read_quote(const char** pcode, char chr) {
    return {true, make_cons(intern("QUOTE"), make_cons(__read(pcode), nil))};
}

reader_macro_result_t read_list(const char** pcode, char chr) {
    // TODO: support the consing dot
    char x;
    object_t value = make_cons(nil, nil);
    object_t tail = value;

    while (true) {
        x = read_char(pcode);
        if (x == EOF)
            error("End of file.");

        if (x == ')')
            return {true, cdr(value)};

        unread_char(pcode);
        tail = cdr(rplacd(tail, make_cons(__read(pcode), nil)));
    }
}

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

object_t read_token(const char* buf) {
    char *endp;
    int value;

    if (*buf == '\0')
        return intern("");

    errno = 0;
    value = strtol(buf, &endp, 10);

    if (*endp != '\0')
        return intern(buf);

    if (errno)
        error("Number range error.");

    return make_int(value);
}

object_t __read(const char** pcode) {
    char x, y, z;
    char *buf = read_buf;
    reader_macro_result_t reader_macro_result;

    memset(read_buf, 0, read_buf_size);

step1:
    x = read_char(pcode);
    if (x == EOF)
        error("End of file.");

step2:
    if (is_invalid_character(x))
        error("Invalid character.");

step3:
    if (x == ' ' || x == '\t' || x == '\n' || x == '\r')
        goto step1;

step4:
    if (x == '"') {
        reader_macro_result = read_string(pcode, '"');
        assert(reader_macro_result.has_value);
        return reader_macro_result.value;
    }

    if (x == '#')
        error("Reader macro character \"#\" is not supported.");

    if (x == '\'') {
        reader_macro_result = read_quote(pcode, '\'');
        assert(reader_macro_result.has_value);
        return reader_macro_result.value;
    }

    if (x == '(') {
        reader_macro_result = read_list(pcode, '(');
        assert(reader_macro_result.has_value);
        return reader_macro_result.value;
    }

    if (x == ')') {
        read_right_paren(pcode);  // no return
        assert(false);
    }

    if (x == ',')
        error("Reader macro character \",\" is not supported.");

    if (x == ';') {
        reader_macro_result = read_comment(pcode);
        assert(!reader_macro_result.has_value);
        goto step1;
    }

    if (x == '`')
        error("Reader macro character \"`\" is not supported.");

step5:
    if (x == '\\') {
        y = read_char(pcode);
        if (y == EOF)
            error("End of file.");

        *buf++ = y;
        if (buf - read_buf == read_buf_size)
            error("Too long token.");

        goto step8;
    }

step6:
    if (x == '|')
        goto step9;

step7:
    *buf++ = toupper(x);
    if (buf - read_buf == read_buf_size)
        error("Too long token.");
    goto step8;

step8:
    y = read_char(pcode);
    if (y == EOF)
        goto step10;

    if (y == '\\') {
        z = read_char(pcode);
        if (z == EOF)
            error("End of file.");

        *buf++ = z;
        if (buf - read_buf == read_buf_size)
            error("Too long token.");

        goto step8;
    }

    if (y == '|')
        goto step9;

    if (is_invalid_character(y))
        error("Invalid character.");

    if (y == '"' || y == '\'' || y == '(' || y == ')' || y == ',' ||
        y == ';' || y == '`') {
        unread_char(pcode);
        goto step10;
    }

    if (y == ' ' || y == '\t' || y == '\n' || y == '\r')
        goto step10;

    *buf++ = toupper(y);
    if (buf - read_buf == read_buf_size)
        error("Too long token.");
    goto step8;

step9:
    y = read_char(pcode);
    if (y == EOF)
        error("End of file.");

    if (y == '\\') {
        z = read_char(pcode);
        if (z == EOF)
            error("End of file");

        *buf++ = z;
        if (buf - read_buf == read_buf_size)
            error("Too long token.");
        goto step9;
    }

    if (y == '|')
        goto step8;

    if (is_invalid_character(y))
        error("Invalid character.");

    *buf++ = y;
    if (buf - read_buf == read_buf_size)
        error("Too long token.");
    goto step9;

step10:
    return read_token(read_buf);
}

object_t read(const char* code) {
    return __read(&code);
}
