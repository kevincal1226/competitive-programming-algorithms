#include "MinimumQueue.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <optional>
#include <print>
#include <random>
#include <ranges>
#include <vector>

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
TEST(TestMinQueue, TestMinSubarrayRandom) {
    std::vector<int> nums{1000};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist(-100, 100);
    for (int &val : std::views::all(nums)) {
        val = dist(gen);
    }
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
