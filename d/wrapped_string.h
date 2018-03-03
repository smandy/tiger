#pragma once

#include <string>

struct WrappedString {
    size_t length;
    char *buf;
    operator std::string();
};
