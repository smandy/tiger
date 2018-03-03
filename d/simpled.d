import core.stdc.string;
import std.stdio;
import std.string;
import core.stdc.stdlib : malloc, free;

enum defaultsize = 128;

alias StringType = WrappedString!defaultsize;
alias IfaceType = FooInterface!defaultsize;

extern (C++) struct WrappedString(int N = 128)
{
    char[N] buf;
}

auto wrap(string s)
{
    StringType ret;
    strncpy(ret.buf.ptr, s.ptr, defaultsize);
    return ret;
}

extern (C++) class FooInterface(int N)
{
    StringType doit()
    {
        writefln("doit()");
        return "Hello from D".wrap();
    }

    StringType doitAgain()
    {
        writefln("doitagain()");
        return "Hello again from D".wrap();
    }
}

extern (C++) struct DAdapter
{
    void run();
}

extern (C++) DAdapter* createInstance(size_t, char**, IfaceType);

extern (C++) void deleteInstance(DAdapter*);

void main(string[] args)
{
    writefln("Woot");
    IfaceType iface;
    char** tmp = cast(char**) malloc(args.length + 1);
    scope (exit)
    {
        free(tmp);
    }
    foreach (i, x; args)
    {
        tmp[i] = cast(char*) args[i].toStringz();
    }
    tmp[args.length] = nullptr;

    DAdapter* da = createInstance(args.length, tmp, iface);
    scope (exit)
    {
        deleteInstance(da);
    }
    da.run();Ice.Trace.Network=1
}
