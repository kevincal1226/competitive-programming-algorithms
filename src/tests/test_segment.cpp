#include "SegmentTree.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <print>
#include <random>
#include <ranges>
#include <set>
#include <sys/types.h>
#include <vector>

TEST(TestSegmentTree, TestRangeSum) {
    std::vector<int> input{-2, 6, 1, 2, 0, -5, 3, 6, 8, 8, 1};
    SegmentTree<int> st(input.begin(), input.end());
    for (size_t i : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
        for (size_t j : std::ranges::iota_view<size_t, size_t>(i, input.size())) {
            ASSERT_EQ(std::accumulate(input.begin() + i, input.begin() + j + 1, 0), st.query(i, j))
                << "Failed range from [" << i << ", " << j << "]\n";
        }
    }
}

TEST(TestSegmentTree, TestRangeSumRandom) {
    std::vector<int> input{1000};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist(-100, 100);

    for (int &val : input) {
        val = dist(gen);
    }
    SegmentTree<int> st(input.begin(), input.end());
    for (size_t i : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
        for (size_t j : std::ranges::iota_view<size_t, size_t>(i, input.size())) {
            ASSERT_EQ(std::accumulate(input.begin() + i, input.begin() + j + 1, 0), st.query(i, j))
                << "Failed range from [" << i << ", " << j << "]\n";
        }
    }
}

TEST(TestSegmentTree, TestCustomMerge) {
    std::vector<int> input{-2, 6, 1, 2, 0, -5, 3, 6, 8, 8, 1};
    SegmentTree<int, decltype([](const int lhs, const int rhs) { return std::max(lhs, rhs); })> st(input.begin(),
                                                                                                   input.end());
    for (size_t i : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
        for (size_t j : std::ranges::iota_view<size_t, size_t>(i, input.size())) {
            ASSERT_EQ(*std::max_element(input.begin() + i, input.begin() + j + 1), st.query(i, j))
                << "Failed range from [" << i << ", " << j << "]\n";
        }
    }
}

TEST(TestSegmentTree, TestUpdateRangeSum) {
    std::string input{"abcdefgh"};
    SegmentTree<std::string> st(input.begin(), input.end());

    for (size_t idx : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
        input[idx] = 'x';
        st.update(idx, "x");
        for (size_t i : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
            for (size_t j : std::ranges::iota_view<size_t, size_t>(i, input.size())) {
                ASSERT_EQ(input.substr(i, j - i + 1), st.query(i, j))
                    << "Failed range from [" << i << ", " << j << "]\n";
            }
        }
        input[idx] = 'a' + idx;
        st.update(idx, std::string{input[idx]});
    }
}

TEST(TestSegmentTree, TestUpdateCustomMerge) {
    std::string input{"abcdefghijklmjklmnopqrstuvwxyz"};
    SegmentTree<char, decltype([](const char lhs, const char rhs) { return std::max(lhs, rhs); })> st(input.begin(),
                                                                                                      input.end());
    for (size_t idx : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
        input[idx] = 'x';
        st.update(idx, 'x');
        for (size_t i : std::ranges::iota_view<size_t, size_t>(0, input.size())) {
            for (size_t j : std::ranges::iota_view<size_t, size_t>(i, input.size())) {
                ASSERT_EQ(*std::max_element(input.begin() + i, input.begin() + j + 1), st.query(i, j))
                    << "Failed range from [" << i << ", " << j << "]\n";
            }
        }
        input[idx] = 'a' + idx;
        st.update(idx, input[idx]);
    }
}
