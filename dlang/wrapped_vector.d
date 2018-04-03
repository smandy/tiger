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

