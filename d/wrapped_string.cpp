#include "wrapped_string.h"

WrappedString::operator std::string() { return std::string(buf); };
