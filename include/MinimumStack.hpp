#pragma once
#ifndef MINIMUM_STACK_H
#define MINIMUM_STACK_H

#include <optional>
#include <stack>
template <typename T, typename Comp = std::less<T>> class MinimumStack {
  public:
    MinimumStack(Comp comp = Comp()) : _st(std::stack<std::pair<T, T>>()), _comp(comp) {}

    ~MinimumStack() = default;

    [[nodiscard]] auto size() -> size_t;

    [[nodiscard]] auto empty() -> bool { return _st.empty(); }

    auto addElement(const T &elem) -> void;

    auto removeElement() -> std::optional<T>;

    [[nodiscard]] auto getMin() -> std::optional<T>;

  private:
    std::stack<std::pair<T, T>> _st;
    Comp _comp;
};

template <typename T, typename Comp> auto MinimumStack<T, Comp>::size() -> size_t { return _st.size(); }

template <typename T, typename Comp> auto MinimumStack<T, Comp>::addElement(const T &elem) -> void {
    T newmin = _st.empty() ? elem : std::min(elem, _st.top().second, _comp);
    _st.emplace(elem, newmin);
}

template <typename T, typename Comp> auto MinimumStack<T, Comp>::removeElement() -> std::optional<T> {
    if (_st.empty()) {
        return std::nullopt;
    }
    T removedElement = _st.top().first;
    _st.pop();
    return removedElement;
}

template <typename T, typename Comp> auto MinimumStack<T, Comp>::getMin() -> std::optional<T> {
    if (_st.empty()) {
        return std::nullopt;
    }
    return _st.top().second;
}

#endif
