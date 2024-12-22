#include "../include/MinimumStack.hpp"

MinimumStack::MinimumStack(const MinimumStack &lhs) {
    if (this == &lhs) {
        return;
    }
    this->_st = lhs._st;
}

auto MinimumStack::size() -> size_t { return _st.size(); }

auto MinimumStack::addElement(const int elem) -> void {
    int newmin = _st.empty() ? elem : std::min(elem, _st.top().second);
    _st.emplace(elem, newmin);
}

auto MinimumStack::removeElement() -> std::optional<int> {
    if (_st.empty()) {
        return std::nullopt;
    }
    int removedElement = _st.top().first;
    _st.pop();
    return removedElement;
}
auto MinimumStack::getMin() -> std::optional<int> {
    if (_st.empty()) {
        return std::nullopt;
    }
    return _st.top().second;
}
