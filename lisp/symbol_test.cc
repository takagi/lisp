#include "symbol.c"

#include <gtest/gtest.h>

#include "test_util.h"

TEST(SymbolTest, InternTest) {
    {
        object_t x = intern("FOO");
        EXPECT_TRUE(is_symbol(x));
        EXPECT_STREQ(symbol_name(x), "FOO");
    }
    {
        object_t x = intern("FOO");
        object_t y = intern("FOO");
        EXPECT_EQ(x, y);
    }
    {
        object_t x = intern("FOO");
        object_t y = make_symbol("FOO");
        EXPECT_NE(x, y);
    }
}
