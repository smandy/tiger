#!/usr/bin/env python

print "Woot"

import Ice

Ice.loadSlice('../slice/SimpleService.ice')
import argo

communicator = Ice.initialize( [ '--Ice.Config=discoveryClient.properties'])
servicePrx = argo.SimpleServicePrx.checkedCast( communicator.stringToProxy('instance@SimpleServiceImpl'))

print servicePrx.sayHello("Andy")
print servicePrx.add( 2,2)
print servicePrx.multiply( 12,12)

communicator.waitForShutdown()

