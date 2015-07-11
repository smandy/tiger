#!/usr/bin/env python

import Ice
import sys

Ice.loadSlice('../slice/Foo.ice')

import argo

class MyFoo( argo.Foo):
    def doit(self, current):
        print "Python doit"
        return "doit from python"

    def doitAgain(self, current):
        print "Python doitagain"
        return "doitAgain from python"

if __name__=='__main__':
    communicator = Ice.initialize(sys.argv)
    print "Woot I've started up"
    adapter = communicator.createObjectAdapter("SimpleApp")

    print "Create impl"
    foo = MyFoo()
    adapter.add( foo, communicator.stringToIdentity('foo'))
    print "Adapter is %s" % adapter
    adapter.activate()
    print "Waiting for shutdown"
    communicator.waitForShutdown()
    print "Shutting down"
    
