#!/usr/bin/env python
from discoverExperiment import communicator

import argo

class MyService( argo.SimpleService):
    def sayHello(self, person, current):
        return "Hello %s!" % person
    
    def add(self, x, y, current):
        return x + y

    def multiply(self, x, y, current):
        return x * y

# NB very important couldn't get discovery to work unless had the adapter defined in config
# I think this depends on the adapterid property
adapter = communicator.createObjectAdapter("SimpleServiceImpl")

adapter.add(MyService(), communicator.stringToIdentity("hello"))
adapter.activate()

print("Wait for shutdown")

communicator.waitForShutdown()



