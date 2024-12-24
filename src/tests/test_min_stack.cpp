#include "MinimumStack.hpp"
#include <gtest/gtest.h>

TEST(TestMinStack, TestInitiallyEmpty) {
    MinimumStack<int> ms{};
    ASSERT_EQ(ms.size(), 0);
    ASSERT_EQ(ms.empty(), true);
    ASSERT_EQ(ms.removeElement(), std::nullopt);
    ASSERT_EQ(ms.getMin(), std::nullopt);
}

TEST(TestMinStack, TestSmall) {
    MinimumStack<int> ms{};
    ms.addElement(10);
    ms.addElement(15);
    ms.addElement(6);
    ms.addElement(3);
    ASSERT_EQ(ms.size(), 4);
    ASSERT_EQ(ms.getMin(), 3);
    ms.removeElement();
    ASSERT_EQ(ms.getMin(), 6);
    ms.removeElement();
    ASSERT_EQ(ms.getMin(), 10);
    ms.removeElement();
    ASSERT_EQ(ms.getMin(), 10);
}

TEST(TestMinStack, TestCustomComp) {
    MinimumStack<int, std::greater<>> ms{};
    ms.addElement(1);
    ms.addElement(0);
    ms.addElement(10);
    ms.addElement(3);
    ASSERT_EQ(ms.getMin(), 10);
    ms.removeElement();
    ASSERT_EQ(ms.getMin(), 10);
    ms.removeElement();
    ASSERT_EQ(ms.getMin(), 1);
    ms.removeElement();
    ASSERT_EQ(ms.getMin(), 1);
}
