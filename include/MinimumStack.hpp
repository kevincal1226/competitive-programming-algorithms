#pragma once

#include <optional>
#include <stack>
#include <utility>

class MinimumStack {
  public:
    MinimumStack() = default;

    ~MinimumStack() = default;

    MinimumStack(MinimumStack &&) = delete;

    MinimumStack &operator=(const MinimumStack &) = default;

    MinimumStack &operator=(MinimumStack &&) = delete;

    explicit MinimumStack(std::stack<std::pair<int, int>> st) : _st(std::move(st)) {}

    MinimumStack(const MinimumStack &lhs);

    auto size() -> size_t;

    auto addElement(int elem) -> void;

    auto removeElement() -> std::optional<int>;

    auto getMin() -> std::optional<int>;

  private:
    std::stack<std::pair<int, int>> _st;
};
