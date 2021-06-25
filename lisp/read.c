#include "read.h"

#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "assert.h"
#include "error.h"
#include "symbol.h"

#define READ_BUF_SIZE 256

char read_buf[READ_BUF_SIZE];

object_t __read_impl(const char** pcode);

bool is_invalid_character(char x) {
    return false;
}

bool is_whitespace(char x) {
    return x == ' ' || x == '\t' || x == '\n' || x == '\r';
}

bool is_terminating_character(char x) {
    return (x == '"' || x == '\'' || x == '(' || x == ')' || x == ',' ||
            x == ';' || x == '`');
}

bool is_delimiter(char x) {
    return is_whitespace(x) || is_terminating_character(x);
}

char read_char(const char** pcode) {
    if (**pcode == '\0') {
        return '\0';
    } else {
        return *(*pcode)++;
    }
}

void unread_char(const char** pcode) {
    (*pcode)--;
}

OPTIONAL(object_t) read_string(const char** pcode, char chr) {
    char x, y;
    char *buf = read_buf;

    while (true) {
        x = read_char(pcode);
        if (x == '\0') {
            error("End of file.");
        }

        if (x == chr) {
            return (OPTIONAL(object_t)){true, make_string(read_buf)};
        }

        if (x == '\\') {
            y = read_char(pcode);
            if (y == '\0') {
                error("End of file.");
            }

            *buf++ = y;
            if (buf - read_buf == READ_BUF_SIZE) {
                error("Too long string.");
            }
            continue;
        }

        *buf++ = x;
        if (buf - read_buf == READ_BUF_SIZE) {
            error("Too long string.");
        }
    }
}

OPTIONAL(object_t) read_quote(const char** pcode, char chr) {
    return (OPTIONAL(object_t)){
        true, make_cons(intern("QUOTE"), make_cons(__read_impl(pcode), nil))};
}

object_t read_after_dot(const char** pcode) {
    signed char x;
    object_t result;

step1:
    x = read_char(pcode);
    if (x == '\0')
        error("End of file.");

step2:
    if (is_invalid_character(x))
        error("Invalid character.");

step3:
    if (x == ' ' || x == '\t' || x == '\n' || x == '\r')
        goto step1;

step4:
    if (x == ')')
        error("Nothing appears after . in list.");

step5:
    unread_char(pcode);
    result = __read_impl(pcode);

step6:
    x = read_char(pcode);
    if (x == '\0')
        error("End of file.");

step7:
    if (is_invalid_character(x))
        error("Invalid character.");

step8:
    if (x == ' ' || x == '\t' || x == '\n' || x == '\r')
        goto step6;

step9:
    if (x == ')')
        return result;

step10:
    error("More than one object follows . in list.");
}

OPTIONAL(object_t) read_list(const char** pcode, char chr) {
    char x, y;
    object_t value = make_cons(nil, nil);
    object_t tail = value;

    while (true) {
        x = read_char(pcode);
        if (x == '\0')
            error("End of file.");

        if (x == ')')
            return (OPTIONAL(object_t)){true, cdr(value)};

        if (x == '.') {
            if (eq(value, tail))
                error("Nothing appears before . in list.");
            y = read_char(pcode);
            unread_char(pcode);
            if (is_delimiter(y)) {
                rplacd(tail, read_after_dot(pcode));
                return (OPTIONAL(object_t)){true, cdr(value)};
            }
        }

        unread_char(pcode);
        tail = cdr(rplacd(tail, make_cons(__read_impl(pcode), nil)));
    }
}

OPTIONAL(object_t) read_right_paren(const char** pcode) {
    error("Unmatched close parenthesis.");
}

OPTIONAL(object_t) read_comment(const char** pcode) {
    char x;

    while (true) {
        x = read_char(pcode);
        if (x == '\0' || x == '\n') {
            return (OPTIONAL(object_t)){false, nil};
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

object_t __read_impl(const char** pcode) {
    signed char x, y, z;
    char *buf = read_buf;
    OPTIONAL(object_t) result;

    memset(read_buf, 0, READ_BUF_SIZE);

step1:
    x = read_char(pcode);
    if (x == '\0')
        error("End of file.");

step2:
    if (is_invalid_character(x))
        error("Invalid character.");

step3:
    if (x == ' ' || x == '\t' || x == '\n' || x == '\r')
        goto step1;

step4:
    if (x == '"') {
        result = read_string(pcode, '"');
        assert(result.has_value);
        return result.value;
    }

    if (x == '#')
        error("Reader macro character \"#\" is not supported.");

    if (x == '\'') {
        result = read_quote(pcode, '\'');
        assert(result.has_value);
        return result.value;
    }

    if (x == '(') {
        result = read_list(pcode, '(');
        assert(result.has_value);
        return result.value;
    }

    if (x == ')') {
        read_right_paren(pcode);  // no return
        assert(false);
    }

    if (x == ',')
        error("Reader macro character \",\" is not supported.");

    if (x == '.')
        error("Dot context error.");

    if (x == ';') {
        result = read_comment(pcode);
        assert(!result.has_value);
        goto step1;
    }

    if (x == '`')
        error("Reader macro character \"`\" is not supported.");

step5:
    if (x == '\\') {
        y = read_char(pcode);
        if (y == '\0')
            error("End of file.");

        *buf++ = y;
        if (buf - read_buf == READ_BUF_SIZE)
            error("Too long token.");

        goto step8;
    }

step6:
    if (x == '|')
        goto step9;

step7:
    *buf++ = toupper(x);
    if (buf - read_buf == READ_BUF_SIZE)
        error("Too long token.");
    goto step8;

step8:
    y = read_char(pcode);
    if (y == '\0')
        goto step10;

    if (y == '\\') {
        z = read_char(pcode);
        if (z == '\0')
            error("End of file.");

        *buf++ = z;
        if (buf - read_buf == READ_BUF_SIZE)
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
    if (buf - read_buf == READ_BUF_SIZE)
        error("Too long token.");
    goto step8;

step9:
    y = read_char(pcode);
    if (y == '\0')
        error("End of file.");

    if (y == '\\') {
        z = read_char(pcode);
        if (z == '\0')
            error("End of file");

        *buf++ = z;
        if (buf - read_buf == READ_BUF_SIZE)
            error("Too long token.");
        goto step9;
    }

    if (y == '|')
        goto step8;

    if (is_invalid_character(y))
        error("Invalid character.");

    *buf++ = y;
    if (buf - read_buf == READ_BUF_SIZE)
        error("Too long token.");
    goto step9;

step10:
    return read_token(read_buf);
}

object_t __read(const char* code) {
    return __read_impl(&code);
}
