#!/usr/bin/env python

print("Woot")
import Ice

Ice.loadSlice('../slice/SimpleService.ice')
import argo

communicator = Ice.initialize( [ '--Ice.Config=discoveryClient.properties'])
# Either of these cals seem to work if the adpaterid is defined
servicePrx = argo.SimpleServicePrx.checkedCast( communicator.stringToProxy('hello'))
#servicePrx = argo.SimpleServicePrx.checkedCast( communicator.stringToProxy('hello@SimpleServiceImpl'))

print(servicePrx.sayHello("Andy"))
print(servicePrx.add( 2,2))
print(servicePrx.multiply( 12,12))

communicator.waitForShutdown()

