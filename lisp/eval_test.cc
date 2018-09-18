#include "lisp/eval.cc"

#include <gtest/gtest.h>

#include "lisp/symbol.h"


TEST(EvalTest, EvalSymbolTest) {
    {
        object_t lenv = lexenv_add_variable(intern("x"), make_int(1),
                          empty_lexenv());
        EXPECT_EQ(eval_symbol(intern("x"), lenv), make_int(1));
    }
    {
        object_t lenv = empty_lexenv();
        EXPECT_DEATH(eval_symbol(intern("x"), lenv), "Variable not found.");
    }
}
