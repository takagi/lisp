#include "prin1.c"

#include <gtest/gtest.h>

TEST(Prin1Test, Prin1Test) {
    {
        testing::internal::CaptureStdout();
        prin1(make_int(1));
        const char* str = testing::internal::GetCapturedStdout().c_str();
        EXPECT_STREQ(str, "1");
    }
    {
        testing::internal::CaptureStdout();
        prin1(nil);
        const char* str = testing::internal::GetCapturedStdout().c_str();
        EXPECT_STREQ(str, "()");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_cons(make_symbol("FOO"), make_symbol("BAR")));
        const char* str = testing::internal::GetCapturedStdout().c_str();
        EXPECT_STREQ(str, "(FOO . BAR)");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_cons(make_symbol("FOO"),
                make_cons(make_symbol("BAR"), nil)));
        const char* str = testing::internal::GetCapturedStdout().c_str();
        EXPECT_STREQ(str, "(FOO BAR)");
    }
    {
        testing::internal::CaptureStdout();
        prin1(make_symbol("FOO"));
        const char* str = testing::internal::GetCapturedStdout().c_str();
        EXPECT_STREQ(str, "FOO");

    }
    {
        testing::internal::CaptureStdout();
        prin1(make_string("foo"));
        const char* str = testing::internal::GetCapturedStdout().c_str();
        EXPECT_STREQ(str, "\"foo\"");
    }
}
