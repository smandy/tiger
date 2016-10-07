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

adapter = communicator.createObjectAdapterWithEndpoints("SimpleServiceImpl", "tcp")

adapter.add(MyService(), communicator.stringToIdentity("hello"))
adapter.activate()

communicator.waitForShutdown()



