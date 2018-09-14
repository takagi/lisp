#include "lisp/lexenv.cc"

#include <gtest/gtest.h>

#include "lisp/symbol.h"


TEST(LexenvTest, EmptyLexenvTest) {
    {
        EXPECT_EQ(empty_lexenv(), nil);
    }
}
