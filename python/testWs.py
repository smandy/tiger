import Ice
Ice.loadSlice('../slice/Foo.ice')

import argo

communicator = Ice.initialize( [ '--Ice.Config=locator.properties'])
#pyPrx = communicator.stringToProxy('foo@SimpleApp')
pyPrx = communicator.stringToProxy('foo@SimpleApp').ice_timeout(500)
x =  pyPrx.ice_getConnection().getInfo()

print pyPrx, x

pyPrx.ice_ping()
print pyPrx
foo = argo.FooPrx.checkedCast( pyPrx)
print "Woot"
print foo
print foo.doit()
print "Boot"
