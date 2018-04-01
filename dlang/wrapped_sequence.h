#pragma once

#include <vector>

template <typename T>
struct WrappedVector {
    size_t length;
    T *buf;
    int i;
    //operator std::vector<T>();
};

template<typename T>
WrappedVector<T> wrap(std::vector<T>& v) {
    WrappedVector<T> ret;
    //ret.buf = new T[v.size()];
    ret.buf = v.data();
    ret.length = v.size();
    ret.i = 0;
    //memcpy(ret.buf, v.data(), sizeof(T) * v.size());
    return ret;
};
