import Ice

Ice.loadSlice('../slice/Hello.ice')

import Demo
communicator = Ice.initialize( [ '--Ice.Config=discovery.properties'])
hello        = communicator.stringToProxy('hello')

print "Before ping"
hello.ice_ping()
print "After ping"
hello = Demo.HelloPrx.checkedCast( hello)
print hello.sayHello("Python")

