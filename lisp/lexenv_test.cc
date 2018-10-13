#include "lexenv.c"

#include <gtest/gtest.h>

#include "cons.h"
#include "list.h"
#include "symbol.h"
#include "test_util.h"

TEST(LexenvTest, EmptyLexenvTest) {
    {
        EXPECT_TRUE(list_equal(empty_lexenv(), cons(nil, nil)));
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

// lexenv_add_symbol_macro

// lexenv_add_function

// lexenv_add_macro

// lexenv_add_block_tag

// lexenv_add_go_tag

// lexenv_add_declaration

TEST(LexenvTest, LexenvFindVariableTest) {
    {
        // A variable
        object_t lenv = lexenv_add_variable(intern("x"), make_int(1),
                          empty_lexenv());
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((OPTIONAL(object_t)){true, make_int(1)}));
    }
    {
        // Variables
        object_t lenv = lexenv_add_variable(intern("y"), make_int(2),
                          lexenv_add_variable(intern("x"), make_int(1),
                            empty_lexenv()));
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((OPTIONAL(object_t)){true, make_int(1)}));
    }
    {
        // Shadowing
        object_t lenv = lexenv_add_variable(intern("x"), make_int(2),
                          lexenv_add_variable(intern("x"), make_int(1),
                            empty_lexenv()));
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((OPTIONAL(object_t)){true, make_int(2)}));
    }
    {
        // Not found
        object_t lenv = empty_lexenv();
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((OPTIONAL(object_t)){false, nil}));
    }
    {
        // Variable in another frame cannot be seen
        object_t lenv = lexenv_new_frame(
                          lexenv_add_variable(intern("x"), make_int(1),
                            empty_lexenv()));
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((OPTIONAL(object_t)){false, nil}));
    }
    {
        // Invalid type
        object_t lenv = empty_lexenv();
        EXPECT_DEATH(lexenv_find_variable(make_int(1), lenv), "Invalid type.");
    }
}

// lexenv_find_function

// lexenv_find_block_tag

// lexenv_find_go_tag

// lexenv_declarations
