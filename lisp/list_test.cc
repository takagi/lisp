#include "lisp/list.cc"

#include <gtest/gtest.h>

#include "lisp/cons.h"


TEST(ListTest, IsListTest) {
    {
        object_t x = make_cons(make_int(1), make_int(2));
        EXPECT_TRUE(is_list(x));
    }
    {
        EXPECT_TRUE(is_list(nil));
    }
    {
        EXPECT_FALSE(is_list(make_int(1)));
    }
}

TEST(ListTest, ListEqualTest) {
    {
        object_t x = cons(make_int(2), cons(make_int(1), nil));
        object_t y = cons(make_int(2), cons(make_int(1), nil));
        EXPECT_TRUE(list_equal(x, y));
        EXPECT_NE(x, y);
    }
    {
        object_t x = make_int(1);
        object_t y = cons(make_int(1), nil);
        EXPECT_FALSE(list_equal(x, y));
        EXPECT_FALSE(list_equal(y, x));
    }
    {
        object_t x = cons(make_int(2), nil);
        object_t y = cons(make_int(1), nil);
        EXPECT_FALSE(list_equal(x, y));
    }
    {
        object_t x = cons(make_int(1), cons(nil, nil));
        object_t y = cons(make_int(1), nil);
        EXPECT_FALSE(list_equal(x, y));
    }
}
