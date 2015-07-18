import Ice
import time

for i in range(10):
    communicator = Ice.initialize( [ '--Ice.Config=locator.properties'])
    pyPrx = communicator.stringToProxy('foo@SimpleApp : ws')
    print pyPrx.ice_getConnection().type()
    time.sleep(1)
