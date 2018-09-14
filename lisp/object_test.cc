#include "lisp/object.cc"

#include <gtest/gtest.h>


TEST(ObjectTest, NullTest) {
    {
        EXPECT_TRUE(null(nil));
    }
    {
        EXPECT_FALSE(null(make_int(1)));
    }
}

TEST(ObjectTest, IntTest) {
    {
        object_t x = make_int(1);
        EXPECT_TRUE(is_int(x));
        EXPECT_EQ(int_value(x), 1);
    }
    {
        EXPECT_FALSE(is_int(nil));
    }
}

TEST(ObjectTest, ConsTest) {
    {
        object_t x = make_cons(make_int(1), nil);
        EXPECT_TRUE(is_cons(x));
        EXPECT_EQ(car(x), make_int(1));
        EXPECT_EQ(cdr(x), nil);
    }
    {
        EXPECT_FALSE(is_cons(nil));
    }
    {
        EXPECT_EQ(car(nil), nil);
        EXPECT_EQ(cdr(nil), nil);
    }

    // TODO: rplaca

    // TODO: rplacd
}

TEST(ObjectTest, SymbolTest) {
    {
        object_t x = make_symbol("FOO");
        EXPECT_TRUE(is_symbol(x));
        EXPECT_STREQ(symbol_name(x), "FOO");
    }
    {
        object_t x = make_symbol("FOO");
        object_t y = make_symbol("FOO");
        EXPECT_NE(x, y);
    }
    {
        EXPECT_TRUE(is_symbol(nil));
    }
    {
        object_t x = make_int(1);
        EXPECT_FALSE(is_symbol(x));
    }
    {
        EXPECT_STREQ(symbol_name(nil), "NIL");
    }
}

TEST(ObjectTest, StringTest) {
    {
        object_t x = make_string("Foo");
        EXPECT_TRUE(is_string(x));
        EXPECT_STREQ(string_str(x), "Foo");
    }
}
