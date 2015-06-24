#!/usr/bin/env python

import Ice
import sys

if __name__=='__main__':
    communicator = Ice.initialize(sys.argv)
    print "Woot I've started up"
    adapter = communicator.createObjectAdapter("SimpleApp")
    print "Adapter is %s" % adapter
    adapter.activate()
    print "Waiting for shutdown"
    communicator.waitForShutdown()
    print "Shutting down"
