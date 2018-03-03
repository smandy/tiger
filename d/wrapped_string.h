#pragma once

#include <string>
#include <cstring>

struct WrappedString {
    size_t length;
    char *buf;
    
    operator std::string();

    // WrappedString( const std::string s);
    // ~WrappedString();
};

WrappedString wrap(const std::string s);

