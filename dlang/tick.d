
import wrapped_vector;

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

WrappedVector!Tick wrap(Tick[] ticks) {
    WrappedVector!Tick ret;
    ret.length = ticks.length;
    foreach (i,ref t; ticks) {
        ret.buf[i]  = t;
    }
    ret.i = 0;
    return ret;
};
