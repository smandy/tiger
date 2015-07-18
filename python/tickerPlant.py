#!/usr/bin/env python
import Ice
import sys
import time

Ice.loadSlice('../slice/Ticker.ice')

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
    producer.send_messages( topic, m )

class MyPlant(argo.TickerPlant):
    def __init__(self):
        self.listeners = {}
        self.stocks = [ Stock(x) for x in set(["CSCO.O", "MSFT.O", "VOD.O",
                                               "GLW.O", "PEB.O", 
                                               "PUMA.O", "IBM.O", "AAPL.O", "JDSU.O", 
                                               "JNPR.O", "SOLC.O", "MFNX.O", "C.O",
                                               "A.O", "SPCS.O", "CRA.A", 
                                               "C.O", "MSFT.O", "SNWL.O", "CHINA.O"]) ]
        
    def evict( self, l):
        def ret(*args):
            print "Evicting %s %s" % (l, args)
            del self.listeners[l]
        return ret
            
    def run(self):
        while True:
            print "Tick..."
            self.tick()
            time.sleep(1)

    def sayHello(self, current):
        print "SayHello"
        return "Hello from python!!"

    def subscribe(self, l, cur):
        print "Subscribe %s" % l
        self.listeners[l] = None

    def tick(self):
        tix = []
        for s in self.stocks:
            s.tick()
            tix.append( argo.Tick( s.name, s.bidPx, s.bidPx + s.spread))
            
        for q,v in self.listeners.items():
            print "Ticking %s %s" % (q,v)
            q.begin_onTick( tix, _ex = self.evict(q))
        print "Boop"

        
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
    communicator.waitForShutdown()
    print "Shutting down"
    
