import core.stdc.string;
import std.stdio;
import std.string;
import core.stdc.stdlib : malloc, free;

extern (C++) class FooInterface
{
    string doit()
    {
        writefln("doit()");
        return "Hello from D";
    }

    string doitAgain()
    {
        writefln("doitagain()");
        return "Hello again from D";
    }
}

extern (C++) struct DAdapter
{
    void run();
}

extern (C++) DAdapter* createInstance(size_t, char**, FooInterface);
extern (C++) void deleteInstance(DAdapter*);

void main(string[] args)
{
    writefln("Woot");
    FooInterface iface;
    char** tmp = cast(char**) malloc(args.length + 1);
    scope (exit)
    {
        free(tmp);
    }
    foreach (i, x; args)
    {
        tmp[i] = cast(char*) args[i].toStringz();
    }
    tmp[args.length] = null;
    DAdapter* da = createInstance(args.length, tmp, iface);
    scope (exit)
    {
        deleteInstance(da);
    }
    da.run();
}
