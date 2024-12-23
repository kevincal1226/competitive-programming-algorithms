#include "MinimumQueue.hpp"
#include "MinimumStack.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

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

TEST(TestMinQueue, TestInitiallyEmpty) {
    MinimumQueue<int> mq{};
    ASSERT_EQ(mq.size(), 0);
    ASSERT_EQ(mq.empty(), true);
    ASSERT_EQ(mq.removeElement(), std::nullopt);
    ASSERT_EQ(mq.getMin(), std::nullopt);
}

TEST(TestMinQueue, TestSmall) {
    MinimumQueue<int> mq{};
    mq.addElement(10);
    ASSERT_EQ(mq.getMin(), 10);
    mq.addElement(18);
    ASSERT_EQ(mq.getMin(), 10);
    ASSERT_EQ(mq.removeElement(), 10);
    ASSERT_EQ(mq.getMin(), 18);
    mq.addElement(-1);
    ASSERT_EQ(mq.getMin(), -1);
}

TEST(TestMinQueue, TestCustomComp) {
    MinimumQueue<int, std::greater<>> mq{};
    mq.addElement(10);
    ASSERT_EQ(mq.getMin(), 10);
    mq.addElement(18);
    ASSERT_EQ(mq.getMin(), 18);
    ASSERT_EQ(mq.removeElement(), 10);
    ASSERT_EQ(mq.getMin(), 18);
    mq.addElement(-1);
    ASSERT_EQ(mq.getMin(), 18);
}

TEST(TestMinQueue, TestMinSubarrayOfFixedLength) {
    std::vector<int> nums{5, 3, -1, 2, 6, 3, 8, 8, 1, 2, 3, 0};
    for (const long subarraySize : std::ranges::iota_view<long, long>(1, nums.size() + 1)) {
        MinimumQueue<int> mq{};
        for (const auto &[i, value] : std::views::enumerate(nums)) {
            mq.addElement(value);
            if (i < subarraySize - 1) {
                continue;
            }
            auto testRange = std::ranges::subrange(nums.begin() + i + 1 - subarraySize, nums.begin() + i + 1);
            ASSERT_EQ(mq.getMin().value(), *std::ranges::min_element(testRange))
                << "Failed range of size " << subarraySize << " from indices [" << i + 1 - subarraySize << ", " << i + 1
                << ")" << '\n';
            ;
            mq.removeElement();
        }
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
