import core.stdc.stdlib : malloc, free;
import std.string;

extern(C++)
struct Args {
    size_t argc;
    char **argv;
}

Args convertArgs(string[] args) {
    Args ret;
    char **tmp = cast(char **) malloc(args.length + 1);
    foreach (i, x; args) { tmp[i] = cast(char *) args[i].toStringz(); }
    tmp[args.length] = null;
    ret.argc = args.length;
    ret.argv = tmp;
    return ret;
}
