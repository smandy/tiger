import std.stdio;
import core.stdc.stdlib : malloc, free;
import std.string;

// TODO - these are identical to slice definitions. Maybe can use these!

extern(C++)
struct WrappedVector(T) {
size_t length;
T* buf;
};


extern(C++, argo) {
enum TickDirection { ZERO, UP, DOWN};

struct Tick {
    long symbol;
    double bidPx;
    double askPx;
    TickDirection bidDirection;
    TickDirection askDirection;
};


struct DListener {
    void onTick( WrappedVector!(argo.Tick) ticks) {
        writefln("Received ticks %s", ticks);
    };
};

}
 
extern (C++) struct DAdapter
{
    void run();
}




 
extern (C++) DAdapter* createInstance(size_t, char**, argo.DListener*);

extern (C++) void deleteInstance(DAdapter*);

void main(string[] args) {
    writefln("Woot");
    DListener iface;
    //DAdapter* da = createInstance(cast(char*)args[1].ptr);
    //scope(exit) deleteInstance(da);
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
    DAdapter* da = createInstance(args.length, tmp, &iface);
    scope (exit)
    {
        deleteInstance(da);
    }
    da.run();

    
};
