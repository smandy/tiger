import std.file;
import std.stdio;
import std.algorithm;
import std.range : iota;
import std.array;

import std.random : Random, uniform, choice;
import std.traits;
import tick;

template Prob(N) if( isFloatingPoint!(N) || isNumeric!(N)) {
    struct Prob {
        uint prob;
        N[] values;
    }
}

auto rnd = Random(42);

bool prob(uint n) {
    return uniform(1,n)==(n-1);
}

alias long OrderIDType;
alias int  SecurityID;
alias float PriceType;
alias uint QtyType;

alias Prob!float PriceChangeType;
alias PriceChangeType[PriceType] SpreadChangeType;

struct Book {
    SecurityID id;
    PriceType p;
    PriceType spread;
    SpreadChangeType spreadChangeProb;
    PriceChangeType priceChangeProb;
    Tick tick;

    this(SecurityID _id,
         PriceType _p,
         PriceType _spread,
         SpreadChangeType _spreadChangeProb,
         PriceChangeType _priceChangeProb,
         ) {
        id = _id;
        p = _p;
        spread = _spread;
        spreadChangeProb = _spreadChangeProb;
        priceChangeProb = _priceChangeProb;
        tick.symbol = _id;
    }

    bool onTick() {
        auto havePriceChange = prob(priceChangeProb.prob);
        auto spreadChangeLevel = spreadChangeProb[spread]; // TODO assert
        auto haveSpreadChange = prob(spreadChangeLevel.prob);
        if (haveSpreadChange) {
            spread = choice(spreadChangeLevel.values);
        }
        if (havePriceChange) {
            auto x2 = choice(priceChangeProb.values);
            p = max(10, p + x2);
        }
        if (havePriceChange || haveSpreadChange) {
            auto oldBid = bid;
            auto oldAsk = ask;
            alias td = argo.TickDirection;
            with(tick) {
                //bu.securityId = sec_id;
                bidPx = bid;
                askPx = ask;
                bidDirection = (bid > oldBid) ? td.UP : ( (bid < oldBid) ? td.DOWN : td.ZERO);
                askDirection = (ask > oldAsk) ? td.UP : ( (ask < oldAsk) ? td.DOWN : td.ZERO);
            }
        }
        return havePriceChange || haveSpreadChange;
    }

    @property PriceType bid() {
        return p;
    }

    @property PriceType ask() {
        return p + spread;
    }
}

Book[] books;

static this() {
    books = [12345, 666, 88888, 32451].map!(s => Book(s, 100.0f, 2,
                                                      [ 2 : PriceChangeType(20, [1,3]),
                                                        1 : PriceChangeType(20, [2]),
                                                        3 : PriceChangeType(20, [2])] ,
                                                      PriceChangeType(5, [-2,-1,1,2]))).array;
}


void main() {
    writefln("Woot");
    for (int i = 0;i<100000;++i) {
        foreach(ref book ; books) {
            book.onTick();
        }
        if (i % 1024 == 0) {
            writefln("%s...", i);
        }
    }
}

unittest {
    pragma(msg,"Books are ",typeof(books));
    writefln("Books are %s", books);
    auto xs = iota(0,20).map!( x => {
            pragma(msg, typeof(x));
            return uniform(0,10,rnd);
        }
        ).array;

    void tickBook( ref Book x) {
        x.tick();
    }
    
    writefln("xs are %s", xs);
    // iota(0,1_000_000)
    //     .each!(n => { books.each!tickBook;} );

    for (int i = 0;i<1_000_000;++i) {
        foreach( ref x ; books) {
            x.tick();
        }
    }
    
    writefln("Books are %s", books);

}



