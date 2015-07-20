import Ice
import time

for i in range(10):
    communicator = Ice.initialize( [ '--Ice.Config=locator.properties'])
    pyPrx = communicator.stringToProxy('foo@SimpleApp')
    x =  pyPrx.ice_getConnection().getInfo()
    print x
    break
    time.sleep(1)
