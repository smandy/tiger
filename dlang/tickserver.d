import std.stdio;
import core.stdc.stdlib : malloc, free;
import std.string;
import wrapped_vector;
import tick;

extern(C++) struct DAdapter {
  void run();
}

extern(C++) struct DListener {
    void onTick( Tic
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

