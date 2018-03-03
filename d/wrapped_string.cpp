#include "wrapped_string.h"

#include <cstring>

WrappedString::operator std::string() { return std::string(buf); };

WrappedString wrap(const std::string s) {
    WrappedString ret;
    ret.buf = new char[s.length()+1];
    strncpy(ret.buf, s.c_str(), s.length());
    ret.length = s.length();
    return ret;
};


// WrappedString::WrappedString(const std::string s) {
//     buf = new char[s.length()];
//     strncpy( buf, s.c_str(), s.length());
// };

// WrappedString::~WrappedString() {
//     free(buf);
// };
    
