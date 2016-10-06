#!/usr/bin/env python

import Ice
import sys
from datetime import datetime

print "Starting"
Ice.loadSlice('../slice/Foo.ice')
import argo

class MyFoo( argo.Foo):
    def doit_async(self, cb, current):
        print "Python doit"
        cb.ice_response("doit from python %s" % datetime.now())

    def doitAgain_async(self, cb, current):
        print "Python doitagain"
        cb.ice_respone( "doitAgain from python %s" % datetime.now())

if __name__=='__main__':
    communicator = Ice.initialize(sys.argv)
    print "I've started up"
    adapter = communicator.createObjectAdapter("SimpleApp")
    print "Create impl"
    foo = MyFoo()
    adapter.add( foo, communicator.stringToIdentity('foo'))
    print "Adapter is %s" % adapter
    adapter.activate()
    print "Waiting for shutdown"
    communicator.waitForShutdown()

    print "Destroy adapter"
    adapter.destroy()
    print "Destroy communicator"
    communicator.destroy()
    
