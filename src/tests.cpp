#include "../include/MinimumStack.hpp"
#include <gtest/gtest.h>

TEST(TestMinStack, TestInitiallyEmpty) {
    MinimumStack ms;
    ASSERT_EQ(ms.size(), 0);
}
