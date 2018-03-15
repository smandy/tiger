import core.stdc.string;
import std.stdio;
import std.string;
import core.stdc.stdlib : malloc, free;

extern (C++) struct DAdapter
{
    string doit();
    string doitAgain();
}

extern (C++) DAdapter* createInstance(char*);

extern (C++) void deleteInstance(DAdapter*);

void main(string[] args)
{
    writefln("Woot '%s'", args[1] );
    DAdapter* da = createInstance(cast(char*)args[1].ptr);
    scope (exit)
    {
        deleteInstance(da);
    }
    
    writefln("Da is %s", &da);
    writefln("doit -> %s", da.doit());
    writefln("doitAgain -> %s", da.doitAgain());
}
