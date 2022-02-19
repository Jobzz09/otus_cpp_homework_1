#include <gtest/gtest.h>
#include "mylib.h"

TEST(google_test_version, test1) {
    ASSERT_TRUE(get_version() > 0);
}