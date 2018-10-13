#include "read.c"

#include <gtest/gtest.h>

#include "test_util.h"

TEST(ReadTest, ReadCharTest) {
    {
        const char *x = "foo";
        EXPECT_EQ(read_char(&x), 'f');
        EXPECT_EQ(read_char(&x), 'o');
        EXPECT_EQ(read_char(&x), 'o');
        EXPECT_EQ(read_char(&x), '\0');
        EXPECT_EQ(read_char(&x), '\0');
    }
}

TEST(ReadTest, UnreadCharTest) {
    {
        const char *x = "foo";
        EXPECT_EQ(read_char(&x), 'f');
        unread_char(&x);
        EXPECT_EQ(read_char(&x), 'f');
    }
}

TEST(ReadTest, ReadStringTest) {
    {
        const char *x = "foo\"";  // '"' is already consumed
        EXPECT_EQ(read_string(&x, '"'),
                  ((OPTIONAL(object_t)){true, make_string("foo")}));
    }
    {
        const char *x = "fo\\o\"";  // '"' is already consumed
        EXPECT_EQ(read_string(&x, '"'),
                  ((OPTIONAL(object_t)){true, make_string("foo")}));
    }
    {
        const char *x = "foo";  // '"' is already consumed
        EXPECT_DEATH(read_string(&x, '"'), "End of file.");
    }
    {
        const char *x = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345\"";
        EXPECT_DEATH(read_string(&x, '"'), "Too long string.");
    }
    {
        const char *x = "foo\\";  // '"' is already consumed
        EXPECT_DEATH(read_string(&x, '"'), "End of file.");
    }
}

TEST(ReadTest, ReadQuoteTest) {
    {
        const char *x = "foo";  // ''' is already consumed
        OPTIONAL(object_t) y = read_quote(&x, '\'');
        EXPECT_TRUE(y.has_value);
        EXPECT_EQ(car(y.value), intern("QUOTE"));
        EXPECT_EQ(car(cdr(y.value)), intern("FOO"));
        EXPECT_EQ(car(cdr(cdr(y.value))), nil);
    }
}

TEST(ReadTest, ReadListTest) {
    {
        const char *x = "foo bar)";  // '(' is already consumed
        OPTIONAL(object_t) y = read_list(&x, '(');
        EXPECT_TRUE(y.has_value);
        EXPECT_EQ(car(y.value), intern("FOO"));
        EXPECT_EQ(car(cdr(y.value)), intern("BAR"));
        EXPECT_EQ(car(cdr(cdr(y.value))), nil);
    }
    {
        const char *x = "foo bar";  // '(' is already consumed
        EXPECT_DEATH(read_list(&x, '('), "End of file.");
    }
}

TEST(ReadTest, ReadRightParenTest) {
    {
        const char *x = ")";
        EXPECT_DEATH(read_right_paren(&x), "Unmatched close parenthesis.");
    }
}

TEST(ReadTest, ReadCommentTest) {
    {
        const char *x = "foo";  // ';' is already consumed
        EXPECT_EQ(read_comment(&x), ((OPTIONAL(object_t)){false, nil}));
    }
    {
        const char *x = "foo";  // ';' is already consumed
        auto y = x;
        read_comment(&x);
        EXPECT_EQ(x - y, 3);
    }
}

TEST(ReadTest, ReadTokenTest) {
    {
        const char *x = "FOO";
        EXPECT_EQ(read_token(x), intern("FOO"));
    }
    {
        const char *x = "123F";
        EXPECT_EQ(read_token(x), intern("123F"));
    }
    {
        const char *x = "";
        EXPECT_EQ(read_token(x), intern(""));
    }
    {
        const char *x = "42";
        EXPECT_EQ(read_token(x), make_int(42));
    }
}

TEST(ReadTest, ReadTest) {
    {
        const char *x = "";
        EXPECT_DEATH(__read(x), "End of file.");
    }
    {
        const char *x = " foo";
        EXPECT_EQ(__read(x), intern("FOO"));

        const char *y = "\nfoo";
        EXPECT_EQ(__read(y), intern("FOO"));
    }
    {
        const char *x = "\"foo\"";
        EXPECT_EQ(__read(x), make_string("foo"));
    }
    {
        const char *x = "#";
        EXPECT_DEATH(__read(x), "Reader macro character \"#\" is not supported.");
    }
    {
        const char *x = "'foo";
        object_t y = __read(x);
        EXPECT_EQ(car(y), intern("QUOTE"));
        EXPECT_EQ(car(cdr(y)), intern("FOO"));
        EXPECT_EQ(car(cdr(cdr(y))), nil);
    }
    {
        const char *x = "()";
        object_t y = __read(x);
        //EXPECT_EQ(y, nil);
    }
    {
        const char *x = "(foo bar)";
        object_t y = __read(x);
        EXPECT_EQ(car(y), intern("FOO"));
        EXPECT_EQ(car(cdr(y)), intern("BAR"));
        EXPECT_EQ(car(cdr(cdr(y))), nil);
    }
    {
        const char *x = "(foo";
        EXPECT_DEATH(__read(x), "End of file.");
    }
    {
        const char *x = ")";
        EXPECT_DEATH(__read(x), "Unmatched close parenthesis.");
    }
    {
        const char *x = ",";
        EXPECT_DEATH(__read(x), "Reader macro character \",\" is not supported.");
    }
    {
        const char *x = ";foo";
        EXPECT_DEATH(__read(x), "End of file.");

        const char *y = ";foo\n42";
        EXPECT_EQ(__read(y), make_int(42));
    }
    {
        const char *x = "`";
        EXPECT_DEATH(__read(x), "Reader macro character \"`\" is not supported.");
    }
    {
        const char *x = "\\foo";
        EXPECT_EQ(__read(x), intern("fOO"));

        const char *y = "\\";
        EXPECT_DEATH(__read(y), "End of file.");
    }
    {
        const char *x = "|f|oo";
        EXPECT_EQ(__read(x), intern("fOO"));

        const char *y = "|foo";
        EXPECT_DEATH(__read(y), "End of file.");
    }
    {
        const char *x1 = "foo";
        EXPECT_EQ(__read(x1), intern("FOO"));

        const char *x2 = "f\\oo";
        EXPECT_EQ(__read(x2), intern("FoO"));

        const char *x3 = "f\\";
        EXPECT_DEATH(__read(x3), "End of file.");

        const char *x4 = "f|o|o";
        EXPECT_EQ(__read(x4), intern("FoO"));

        const char *x5 = "f|oo";
        EXPECT_DEATH(__read(x5), "End of file.");

        const char *x6 = "foo(";
        EXPECT_EQ(__read(x6), intern("FOO"));

        const char *x7 = "foo\nbar";
        EXPECT_EQ(__read(x7), intern("FOO"));

        const char *x8 = "|f\\oo|";
        EXPECT_EQ(__read(x8), intern("foo"));
    }
}
