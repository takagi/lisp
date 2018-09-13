#include "lisp/read.cc"

#include <gtest/gtest.h>


TEST(ReadTest, ReadCharTest) {
    {
        const char *x = "foo";
        EXPECT_EQ(read_char(&x), 'f');
        EXPECT_EQ(read_char(&x), 'o');
        EXPECT_EQ(read_char(&x), 'o');
        EXPECT_EQ(read_char(&x), EOF);
        EXPECT_EQ(read_char(&x), EOF);
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

bool operator==(reader_macro_result_t lhs, reader_macro_result_t rhs) {
    assert(lhs.has_value || (!lhs.has_value && lhs.value == nil));
    assert(rhs.has_value || (!rhs.has_value && rhs.value == nil));
    return lhs.has_value == rhs.has_value && lhs.value == rhs.value;
}

bool operator!=(reader_macro_result_t lhs, reader_macro_result_t rhs) {
    return !(lhs == rhs);
}

TEST(ReadTest, ReadStringTest) {
    {
        const char *x = "foo\"";  // '"' is already consumed
        EXPECT_EQ(read_string(&x, '"'),
                  ((reader_macro_result_t){true, make_string("foo")}));
    }
    {
        const char *x = "fo\\o\"";  // '"' is already consumed
        EXPECT_EQ(read_string(&x, '"'),
                  ((reader_macro_result_t){true, make_string("foo")}));
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

TEST(ReadTest, DISABLED_ReadQuoteTest) {
    {
        const char *x = "foo";  // ''' is already consumed
        reader_macro_result_t e = {true, make_cons(intern("QUOTE"),
                                           make_cons(intern("FOO"), nil))};
        EXPECT_EQ(read_quote(&x, '\''), e);
    }
}

// ReadListTest

TEST(ReadTest, ReadRightParenTest) {
    {
        const char *x = ")";
        EXPECT_DEATH(read_right_paren(&x), "Unmatched close parenthesis.");
    }
}

TEST(ReadTest, ReadCommentTest) {
    {
        const char *x = "foo";  // ';' is already consumed
        EXPECT_EQ(read_comment(&x), ((reader_macro_result_t){false, nil}));
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
        EXPECT_DEATH(read(x), "End of file.");
    }
    {
        const char *x = " foo";
        EXPECT_EQ(read(x), intern("FOO"));

        const char *y = "\nfoo";
        EXPECT_EQ(read(y), intern("FOO"));
    }
    {
        const char *x = "\"foo\"";
        EXPECT_EQ(read(x), make_string("foo"));
    }
    {
        const char *x = "#";
        EXPECT_DEATH(read(x), "Reader macro character \"#\" is not supported.");
    }
    {
        const char *x = "'foo";
        object_t y = read(x);
        EXPECT_EQ(car(y), intern("QUOTE"));
        EXPECT_EQ(car(cdr(y)), intern("FOO"));
        EXPECT_EQ(car(cdr(cdr(y))), nil);
    }
    {
        // test list
    }
    {
        const char *x = ")";
        EXPECT_DEATH(read(x), "Unmatched close parenthesis.");
    }
    {
        const char *x = ",";
        EXPECT_DEATH(read(x), "Reader macro character \",\" is not supported.");
    }
    {
        const char *x = ";foo";
        EXPECT_DEATH(read(x), "End of file.");

        const char *y = ";foo\n42";
        EXPECT_EQ(read(y), make_int(42));
    }
    {
        const char *x = "`";
        EXPECT_DEATH(read(x), "Reader macro character \"`\" is not supported.");
    }
    {
        const char *x = "\\foo";
        EXPECT_EQ(read(x), intern("fOO"));

        const char *y = "\\";
        EXPECT_DEATH(read(y), "End of file.");
    }
    {
        const char *x = "|f|oo";
        EXPECT_EQ(read(x), intern("fOO"));

        const char *y = "|foo";
        EXPECT_DEATH(read(y), "End of file.");
    }
    {
        const char *x1 = "foo";
        EXPECT_EQ(read(x1), intern("FOO"));

        const char *x2 = "f\\oo";
        EXPECT_EQ(read(x2), intern("FoO"));

        const char *x3 = "f\\";
        EXPECT_DEATH(read(x3), "End of file.");

        const char *x4 = "f|o|o";
        EXPECT_EQ(read(x4), intern("FoO"));

        const char *x5 = "f|oo";
        EXPECT_DEATH(read(x5), "End of file.");

        const char *x6 = "foo(";
        EXPECT_EQ(read(x6), intern("FOO"));

        const char *x7 = "foo\nbar";
        EXPECT_EQ(read(x7), intern("FOO"));

        const char *x8 = "|f\\oo|";
        EXPECT_EQ(read(x8), intern("foo"));
    }
}
