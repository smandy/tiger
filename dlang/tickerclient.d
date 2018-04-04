import std.stdio;
import core.stdc.stdlib : malloc, free;
import std.string;
import wrapped_vector;
import tick;

extern(C++) struct DAdapter {
  void run();
}

extern(C++) struct DListener {
  void onTick(WrappedVector !(argo.Tick)ticks1) {
    // auto ticks = cast(Tick[]) ticks1;
    // writefln("Received ticks %s", ticks.length);
    // writefln("Buf is %s %s", ticks.buf, ticks.buf[1]);
    // wraitefln("Size is %s", Tick.sizeof);
    foreach (ref tick; ticks1) { writefln("Tick is %s", tick); }
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
