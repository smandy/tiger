#!/usr/bin/env rdmd

import std.stdio;
import std.format;
import std.array;

struct Foo {
    string first;
    string last;

    void doit();
}

template dumpType(T, string member) {
    enum isFunction = __traits(isStaticFunction, __traits(getMember, T.init, member));
    static if (isFunction) {
        enum dumpType = "%s Its a function beeyatch".format(member);
    } else {
        //enum val = T.init;
        enum the_member = __traits(getMember, T.init, member);
        enum sizeOf = the_member.sizeof;
        enum alignOf = __traits(getMember, T.init, member).alignof;
        enum dumpType = format("%s %s %s %s", sizeOf, alignOf, member, isFunction);
    }
    
}

string d_to_ice(T)() {
    string[] ret;
    foreach( member ; __traits(derivedMembers, T)) {
        ret ~= dumpType!(T,member);
    }
    return ret.join(",");
}

void main() {
    writefln("%s", d_to_ice!Foo);
}
