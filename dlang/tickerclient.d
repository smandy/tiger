import std.stdio;
import core.stdc.stdlib : malloc, free;
import std.string;

// TODO - these are identical to slice definitions. Maybe can use these!
extern(C++) struct WrappedVector(T) {
  size_t length;
  T *buf;
  int i;

  T front() {
    // writaefln("Front");
    return buf[i];
  }

  bool empty() {
    // writefln("empty %s %s", i , length);
    return (i + 1) >= length;
  }

  @safe void popFront() {
    // writefln("popfront");
    ++i;
  }
}

extern(C++, argo) {
  enum TickDirection : byte { ZERO, UP, DOWN };

  struct Tick {
    long symbol;
    double bidPx;
    double askPx;
    TickDirection bidDirection;
    TickDirection askDirection;
  }
}

extern(C++) struct DAdapter {
  void run();
}

extern(C++) struct DListener {
  void onTick(WrappedVector !(argo.Tick)ticks1) {
    // auto ticks = cast(Tick[]) ticks1;
    // writefln("Received ticks %s", ticks.length);
    // writefln("Buf is %s %s", ticks.buf, ticks.buf[1]);
    // wraitefln("Size is %s", Tick.sizeof);
      foreach (ref tick; ticks1) { writefln("Tick %s is", tick); }
  }
}

extern(C++) DAdapter *createInstance(size_t, char **, DListener *);

extern(C++) void deleteInstance(DAdapter *);

void main(string[] args) {
  writefln("Woot");
  DListener iface;
  // DAdapter* da = createInstance(cast(char*)args[1].ptr);
  // scope(exit) deleteInstance(da);
  char **tmp = cast(char **) malloc(args.length + 1);
  scope(exit) { free(tmp); }
  foreach (i, x; args) { tmp[i] = cast(char *) args[i].toStringz(); }
  tmp[args.length] = null;
  DAdapter *da = createInstance(args.length, tmp, &iface);
  scope(exit) { deleteInstance(da); }
  da.run();
}
