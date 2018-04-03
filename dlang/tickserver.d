import std.stdio;
import core.stdc.stdlib : malloc, free;
import std.string;
import wrapped_vector;
import tick;
import convertargs;

extern (C++) struct TickReceiver
{
    void receiveTick(WrappedVector!Tick ticks);

    void stop();

    void join();
}

extern (C++) TickReceiver* createInstance(size_t, char**);

void main(string[] args)
{
    writefln("Woot");
    ///DListener iface;
    // DAdapter* da = createInstance(cast(char*)args[1].ptr);
    // scope(exit) deleteInstance(da);
    auto a = convertArgs(args);
    auto tickReceiver = createInstance(a.argc, a.argv);

    writefln("Joining");
    tickReceiver.join();
    writefln("Joined");
}
