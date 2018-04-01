#pragma once

#include <vector>

template <typename T>
struct WrappedVector {
    size_t length;
    T *buf;
    operator std::vector<T>();
};

template<typename T>
WrappedVector<T> wrap(const std::vector<T>& v) {
    WrappedVector<T> ret;
    ret.buf = new T[v.size()];
    ret.length = v.size();
    memcpy(ret.buf, v.data(), sizeof(T) * v.size());
    return ret;
};
