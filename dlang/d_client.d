import core.stdc.string;
import std.stdio;
import std.string;
import core.stdc.stdlib : malloc, free;
import std.conv;

extern (C++) struct DAdapter
{
    string doit();
    string doitAgain();
    int add(int a, int b);
}

extern (C++) DAdapter* createInstance(int, char**);

extern (C++) void deleteInstance(DAdapter*);

void main(string[] args)
{
    writefln("Woot '%s'", args[1] );

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

    DAdapter* da = createInstance(to!int(args.length), tmp);
    scope (exit)
    {
        deleteInstance(da);
    }
    
    writefln("Da is %s", &da);
    writefln("doit -> %s", da.doit());
    writefln("doitAgain -> %s", da.doitAgain());
    writefln("Add %s %s -> %s", 10, 12, da.add(10,12));
}
