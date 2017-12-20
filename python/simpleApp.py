#!/usr/bin/env python

import Ice
import sys
from datetime import datetime

print("Starting")
Ice.loadSlice('../slice/Foo.ice')
import argo

def doLog(s):
    print(s)
    sys.stdout.flush()

class MyFoo( argo.Foo):
    def doit(self, current):
        doLog("Python doit")
        #cb.ice_response("doit from python %s" % datetime.now())
        return("doit from python %s" % datetime.now())

    def doitAgain(self, current):
        doLog("Python doitagain")
        return("doitAgain from python %s" % datetime.now())

if __name__=='__main__':
    communicator = Ice.initialize(sys.argv)
    doLog("I've started up")
    adapter = communicator.createObjectAdapter("SimpleApp")
    doLog("Create impl")
    foo = MyFoo()
    adapter.add( foo, communicator.stringToIdentity('foo'))
    doLog("Adapter is %s" % adapter)
    adapter.activate()
    doLog("Waiting for shutdown")
    sys.stdout.flush()
    communicator.waitForShutdown()

    doLog("Destroy adapter")
    adapter.destroy()
    doLog("Destroy communicator")
    communicator.destroy()
    
