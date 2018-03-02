import core.stdc.string;
import std.stdio;

enum defaultsize = 128;

alias StringType = WrappedString!defaultsize;
alias IfaceType = FooInterface!defaultsize;

extern(C++)
struct WrappedString(int N = 128) {
    char[N] buf;
};

extern(C++)
class FooInterface(int N) {
    StringType doit() {
        return "Hello from D bitches".wrap();
    };
    
    StringType doitAgain() {
        return "Hello again from D bitches".wrap();
    };
};

extern(C++)
struct DAdapter {
    void run();
};

extern(C++)
DAdapter* createInstance(int, char**, IfaceType);

extern(C++)
void deleteInstance(DAdapter*);

auto wrap(string s) {
    StringType ret;
    strncpy(ret.buf.ptr, s.ptr, defaultsize);
    return ret;
};

void main() {
    writefln("Woot");
    IfaceType iface;
    DAdapter* da = createInstance(0, cast(char**)null, iface);
    scope(exit) { deleteInstance(da); }
    da.run();
};
