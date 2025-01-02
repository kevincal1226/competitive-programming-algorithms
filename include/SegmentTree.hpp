#pragma once

#include <stdexcept>
#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <print>
#include <vector>

template <typename T, typename Merge = decltype([](const T &lhs, const T &rhs) { return lhs + rhs; })>
class SegmentTree {
  public:
    template <typename Iterator>
    SegmentTree(Iterator begin, Iterator end, Merge merge = Merge())
        : _merge(merge), _n(std::distance(begin, end)), _data(_n * 4) {
        build(begin, 1, 0, _n - 1);
        // for (auto &x : _data) {
        //     std::println("{}", x);
        // }
    }

    T query(size_t l, size_t r);

    void update(size_t pos, const T &newVal);

    ~SegmentTree() = default;

  private:
    template <typename Iterator> void build(Iterator begin, size_t currVertex, size_t l, size_t r);
    std::optional<T> callQuery(size_t currVertex, size_t vertexL, size_t vertexR, size_t rangeL, size_t rangeR);
    void updateQuery(size_t currVertex, size_t vertexL, size_t vertexR, size_t pos, const T &newVal);

    Merge _merge;
    size_t _n;
    std::vector<T> _data;
};

template <typename T, typename Merge>
std::optional<T> SegmentTree<T, Merge>::callQuery(const size_t currVertex, const size_t vertexL, const size_t vertexR,
                                                  const size_t rangeL, const size_t rangeR) {
    if (rangeL > rangeR) {
        return std::nullopt;
    }

    if (vertexL == rangeL && vertexR == rangeR) {
        return _data[currVertex];
    }

    const size_t vertexM = (vertexL + vertexR) / 2;
    std::optional<T> leftChild = callQuery(currVertex * 2, vertexL, vertexM, rangeL, std::min(vertexM, rangeR));
    std::optional<T> rightChild =
        callQuery(currVertex * 2 + 1, vertexM + 1, vertexR, std::max(rangeL, vertexM + 1), rangeR);
    if (!leftChild.has_value()) {
        return rightChild.value();
    }
    if (!rightChild.has_value()) {
        return leftChild.value();
    }
    return _merge(leftChild.value(), rightChild.value());
}

template <typename T, typename Merge> void SegmentTree<T, Merge>::update(const size_t pos, const T &newVal) {
    updateQuery(1, 0, _n - 1, pos, newVal);
}

template <typename T, typename Merge>
template <typename Iterator>
void SegmentTree<T, Merge>::build(Iterator begin, const size_t currVertex, const size_t l, const size_t r) {
    if (l == r) {
        _data[currVertex] = *(begin + l);
        return;
    }

    const size_t m = (l + r) / 2;
    build(begin, currVertex * 2, l, m);
    build(begin, currVertex * 2 + 1, m + 1, r);
    _data[currVertex] = _merge(_data[currVertex * 2], _data[currVertex * 2 + 1]);
}

template <typename T, typename Merge> T SegmentTree<T, Merge>::query(const size_t l, const size_t r) {
    if (l > r) {
        throw std::invalid_argument("l must be less than or equal to r");
    }
    return callQuery(1, 0, _n - 1, l, r).value();
}

template <typename T, typename Merge>
void SegmentTree<T, Merge>::updateQuery(const size_t currVertex, const size_t vertexL, const size_t vertexR,
                                        const size_t pos, const T &newVal) {
    if (vertexL == vertexR) {
        _data[currVertex] = newVal;
        return;
    }

    const size_t vertexM = (vertexL + vertexR) / 2;
    if (pos <= vertexM) {
        updateQuery(currVertex * 2, vertexL, vertexM, pos, newVal);
    }
    else {
        updateQuery(currVertex * 2 + 1, vertexM + 1, vertexR, pos, newVal);
    }

    _data[currVertex] = _merge(_data[currVertex * 2], _data[currVertex * 2 + 1]);
}

#endif
