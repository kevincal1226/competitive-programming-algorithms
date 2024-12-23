#pragma once
#ifndef MINIMUM_QUEUE_H
#define MINIMUM_QUEUE_H

#include "MinimumStack.hpp"
#include <optional>

template <typename T, typename Comp = std::less<T>> class MinimumQueue {
  public:
    MinimumQueue(Comp comp = Comp()) : _st1(MinimumStack<T, Comp>()), _st2(MinimumStack<T, Comp>()), _comp(comp) {}

    ~MinimumQueue() = default;

    [[nodiscard]] auto size() -> size_t;

    [[nodiscard]] auto empty() -> bool;

    auto addElement(const T &elem) -> void;

    auto removeElement() -> std::optional<T>;

    [[nodiscard]] auto getMin() -> std::optional<T>;

  private:
    MinimumStack<T, Comp> _st1, _st2;
    Comp _comp;
};

template <typename T, typename Comp> auto MinimumQueue<T, Comp>::size() -> size_t { return _st1.size() + _st2.size(); }

template <typename T, typename Comp> auto MinimumQueue<T, Comp>::empty() -> bool {
    return _st1.empty() && _st2.empty();
}

template <typename T, typename Comp> auto MinimumQueue<T, Comp>::addElement(const T &elem) -> void {
    _st1.addElement(elem);
}

template <typename T, typename Comp> auto MinimumQueue<T, Comp>::removeElement() -> std::optional<T> {
    if (_st2.empty()) {
        while (!_st1.empty()) {
            T elem = _st1.removeElement().value();
            _st2.addElement(elem);
        }
    }

    return _st2.removeElement();
}

template <typename T, typename Comp> auto MinimumQueue<T, Comp>::getMin() -> std::optional<T> {
    if (empty()) {
        return std::nullopt;
    }

    if (_st1.empty() || _st2.empty()) {
        return _st1.empty() ? _st2.getMin().value() : _st1.getMin().value();
    }

    return std::min(_st1.getMin().value(), _st2.getMin().value(), _comp);
}

#endif
