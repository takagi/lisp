#include "lisp/lexenv.cc"

#include <gtest/gtest.h>

#include "lisp/symbol.h"


TEST(LexenvTest, EmptyLexenvTest) {
    {
        EXPECT_EQ(empty_lexenv(), nil);
    }
}

TEST(LexenvTest, DISABLED_LexenvAddVariableTest) {
    /*
    {
        object_t lenv = lexenv_add_variable(intern("x"), make_int(1),
                          empty_lexenv());
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv), make_int(1));
    }
    */
}
