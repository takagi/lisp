#include "lisp/object.h"

#include <gtest/gtest.h>


/*
 * Null
 */

TEST(NullTest, NullTest) {
    EXPECT_TRUE(null(nil));
    EXPECT_FALSE(null(make_int(1)));
}


/*
 * Int
 */

TEST(IntTest, IntTest) {
    object_t x = make_int(1);
    EXPECT_TRUE(is_int(x));
    EXPECT_FALSE(is_int(nil));
    EXPECT_EQ(int_value(x), 1);
}


/*
 * Cons
 */

TEST(ConsTest, IsConsTest) {
}

TEST(ConsTest, CarTest) {
/*
    EXPECT_EQ(car(nil), nil);
    EXPECT_EQ(car(t), nil);
    EXPECT_NE(t, nil);
*/
}


/*
 * Symbol
 */

TEST(SymbolTest, MakeSymbolTest) {
    object_t x = make_symbol("FOO");
    EXPECT_TRUE(is_symbol(x));
    EXPECT_STREQ(symbol_name(x), "FOO");

    object_t y = make_symbol("FOO");
    EXPECT_NE(x, y);
}

TEST(SymbolTest, IsSymbolTest) {
    EXPECT_TRUE(is_symbol(nil));

    object_t x = make_int(1);
    EXPECT_FALSE(is_symbol(x));
}

TEST(SymbolTest, SymbolNameTest) {
    EXPECT_STREQ(symbol_name(nil), "NIL");
}


/*
 * String
 */

TEST(ObjectTest, StringTest) {
    {
        object_t x = make_string("Foo");
        EXPECT_TRUE(is_string(x));
        EXPECT_STREQ(string_str(x), "Foo");
    }
}
