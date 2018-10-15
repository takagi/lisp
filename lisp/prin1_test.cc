#include "prin1.c"

#include <gtest/gtest.h>

TEST(Prin1Test, Prin1Test) {
    {
        testing::internal::CaptureStdout();
        prin1(make_int(1));
        std::string str = testing::internal::GetCapturedStdout();
        EXPECT_EQ(str, "1");
    }
    {
        testing::internal::CaptureStdout();
        prin1(nil);
        std::string str = testing::internal::GetCapturedStdout();
        EXPECT_EQ(str, "NIL");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_cons(make_symbol("FOO"), make_symbol("BAR")));
        std::string str = testing::internal::GetCapturedStdout();
        EXPECT_EQ(str, "(FOO . BAR)");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_cons(make_symbol("FOO"),
                make_cons(make_symbol("BAR"), nil)));
        std::string str = testing::internal::GetCapturedStdout();
        EXPECT_EQ(str, "(FOO BAR)");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_symbol("FOO"));
        std::string str = testing::internal::GetCapturedStdout();
        EXPECT_EQ(str, "FOO");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_string("foo"));
        std::string str = testing::internal::GetCapturedStdout();
        EXPECT_EQ(str, "\"foo\"");
    }
}
