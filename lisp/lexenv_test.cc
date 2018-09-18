#include "lisp/lexenv.cc"

#include <gtest/gtest.h>

#include "lisp/cons.h"
#include "lisp/list.h"
#include "lisp/symbol.h"


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

bool operator==(lexenv_find_variable_result_t lhs,
                lexenv_find_variable_result_t rhs) {
    assert(lhs.found || (!lhs.found && lhs.value == nil));
    assert(rhs.found || (!rhs.found && rhs.value == nil));
    return lhs.found == rhs.found && lhs.value == rhs.value;
}

bool operator!=(lexenv_find_variable_result_t lhs,
                lexenv_find_variable_result_t rhs) {
    return !(lhs == rhs);
}

TEST(LexenvTest, LexenvFindVariableTest) {
    {
        // A variable
        object_t lenv = lexenv_add_variable(intern("x"), make_int(1),
                          empty_lexenv());
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((lexenv_find_variable_result_t){true, make_int(1)}));
    }
    {
        // Variables
        object_t lenv = lexenv_add_variable(intern("y"), make_int(2),
                          lexenv_add_variable(intern("x"), make_int(1),
                            empty_lexenv()));
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((lexenv_find_variable_result_t){true, make_int(1)}));
    }
    {
        // Shadowing
        object_t lenv = lexenv_add_variable(intern("x"), make_int(2),
                          lexenv_add_variable(intern("x"), make_int(1),
                            empty_lexenv()));
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((lexenv_find_variable_result_t){true, make_int(2)}));
    }
    {
        // Not found
        object_t lenv = empty_lexenv();
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((lexenv_find_variable_result_t){false, nil}));
    }
    {
        // Variable in another frame cannot be seen
        object_t lenv = lexenv_new_frame(
                          lexenv_add_variable(intern("x"), make_int(1),
                            empty_lexenv()));
        EXPECT_EQ(lexenv_find_variable(intern("x"), lenv),
                  ((lexenv_find_variable_result_t){false, nil}));
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
