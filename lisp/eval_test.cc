#include "eval.c"

#include <gtest/gtest.h>

#include "lexenv.h"
#include "symbol.h"
#include "test_util.h"

TEST(EvalTest, EvalSymbolTest) {
    {
        object_t lenv = lexenv_add_variable(intern("x"), make_int(1),
                          empty_lexenv());
        EXPECT_EQ(eval_symbol(intern("x"), lenv), make_int(1));
    }
    {
        object_t lenv = empty_lexenv();
        EXPECT_EQ(eval_symbol(nil, lenv), nil);
    }
    {
        object_t lenv = empty_lexenv();
        EXPECT_DEATH(eval_symbol(intern("x"), lenv), "Variable not found.");
    }
}

TEST(EvalTest, EvalTest) {
    {
        object_t lenv = lexenv_add_variable(intern("x"), make_int(1),
                          empty_lexenv());
        EXPECT_EQ(__eval(intern("x"), lenv), make_int(1));
    }
    {
        EXPECT_EQ(eval(make_int(1)), make_int(1));
        EXPECT_EQ(eval(make_string("foo")), make_string("foo"));
        EXPECT_EQ(eval(nil), nil);
    }
}
