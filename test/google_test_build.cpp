#include <gtest/gtest.h>
#include "build_number.hpp"

TEST(google_test_version, test1) {
    ASSERT_TRUE(get_build() > 0);
}