import core.stdc.string;
import std.stdio;
import std.string;
import core.stdc.stdlib : malloc;

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
    }
}

extern(C++)
struct DAdapter {
    void run();
};

extern(C++)
DAdapter* createInstance( size_t, char**, IfaceType );

extern(C++)
void deleteInstance(DAdapter*);

auto wrap(string s) {
    StringType ret;
    strncpy(ret.buf.ptr, s.ptr, defaultsize);
    return ret;
};

void main(string[] args) {
    writefln("Woot");
    IfaceType iface;
    char** tmp = cast(char**) malloc( args.length + 1 );
    foreach(i,x ; args) {
        tmp[i] = cast(char*) args[i].toStringz();
    }
    DAdapter* da = createInstance(args.length, tmp, iface);
    scope(exit) { deleteInstance(da); }
    da.run();
};
