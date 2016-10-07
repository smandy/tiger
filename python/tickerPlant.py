#!/usr/bin/env python
import time
import Ice
from datetime import  datetime

## if not slice_dir:
##     print(sys.argv[0] + ': Slice directory not found.')
##     sys.exit(1)
## Ice.loadSlice("'-I" + slice_dir + "' Callback.ice")

slice_dir = Ice.getSliceDir()
Ice.loadSlice('-I %(slice_dir)s ../slice/Ticker.ice' % locals() )

import argo
import random

def randomPrice():
    ret = round( 100.0 + 50.0 * random.random() , 2)
    return ret

def randomSpread():
    return random.choice( [0.01, 0.02] )

class Stock:
    def __init__(self, name):
        self.name = name
        self.bidPx = randomPrice()
        self.spread = randomSpread()

    def tick(self):
        self.bidPx += random.choice( [0.01, -0.01, 0.0])
        self.spread = randomSpread()

stocks = [ Stock(x) for x in set(["CSCO.O", "MSFT.O", "VOD.O",
                                  "GLW.O", "PEB.O", 
                                  "PUMA.O", "IBM.O", "AAPL.O", "JDSU.O", 
                                  "JNPR.O", "SOLC.O", "MFNX.O", "C.O",
                                  "A.O", "SPCS.O", "CRA.A", 
                                  "C.O", "MSFT.O", "SNWL.O", "CHINA.O"]) ]

def tickStocks():
    ret = ["bac:%d" % (time.time() * 1000000)]
    for s in stocks:
        s.tick()
        ret.append( "%s,%s,%s" % (s.name, s.bidPx, s.bidPx + s.spread))
    m = ":".join(ret)
    print m
    #producer.send_messages( topic, m )

class MyPlant(argo.TickerPlant):
    def __init__(self):
        self.listeners = {}
        self.stocks = [ Stock(x) for x in set(["CSCO.O", "MSFT.O", "VOD.O",
                                               "GLW.O", "PEB.O", 
                                               "PUMA.O", "IBM.O", "AAPL.O", "JDSU.O", 
                                               "JNPR.O", "SOLC.O", "MFNX.O", "C.O",
                                               "A.O", "SPCS.O", "CRA.A", 
                                               "C.O", "MSFT.O", "SNWL.O", "CHINA.O"]) ]
        self.running = True
        self.history = []
        
    def evict( self, l):
        def ret(*args):
            #print "Evicting %s %s" % (l, args)
            print "Evicting ...dare not name his name"
            del self.listeners[l]
        return ret
            
    def run(self):
        while self.running:
            #print "Tick..."
            self.tick()
            time.sleep(1)

    def sayHello(self, current):
        noo = datetime.now().isoformat()
        print "SayHello %s" % noo
        return "Hello from python!! %s" % noo

    def subscribe(self, l, cur):
        print "Subscribe %s" % l
        self.listeners[l] = None

    def fail(self, *args):
        print "Fail! %s" % str(args)
        
    def subscribeWithIdent(self, l, cur):
        print "Subscribe with ident %s" % communicator.identityToString(l)
        prx = argo.TickListenerPrx.uncheckedCast(cur.con.createProxy(l))
        prx.begin_onImage( self.history, _ex = self.fail )
        self.listeners[prx] = None

    def tick(self):
        tix = []
        for s in self.stocks:
            s.tick()
            tix.append( argo.Tick( s.name, s.bidPx, s.bidPx + s.spread))
        for q,v in self.listeners.items():
            #print "Ticking %s %s" % (q,v)
            q.begin_onTick( tix, _ex = self.evict(q))
        self.history = (self.history + [tix])[-300:]
        #print "Boop"
        
if __name__=='__main__':
    communicator = Ice.initialize(['--Ice.Config=tickerplant.properties'])
    print "Woot I've started up"
    adapter = communicator.createObjectAdapter("TickerPlant")
    
    print "Create impl"
    plant = MyPlant()
    adapter.add( plant, communicator.stringToIdentity('plant'))
    print "Adapter is %s" % adapter

    import threading
    threading.Thread(target = plant.run).start()
    
    adapter.activate()
    print "Waiting for shutdown"

    try:
        while True:
            time.sleep(1)
    except:
        pass
    #adapter.close()
    #adapter.shutdown()
    plant.running = False
    communicator.destroy()
    #communicator.destroy()
    print "Shutting down"
    
