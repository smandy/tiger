import Ice

from common import getUUID

slice_dir = Ice.getSliceDir()
Ice.loadSlice('-I %(slice_dir)s ../slice/Ticker.ice' % locals())

import argo

class MyListener(argo.TickListener):
    def onTick(self, tix, current):
        print("onTick %s" % tix)

if __name__=='__main__':
    communicator = Ice.initialize(['--Ice.Config=tickerplant.properties'] )
    adapter = communicator.createObjectAdapterWithEndpoints( getUUID(), "tcp" )
    adapter.activate()
    myListener = MyListener()
    prx = argo.TickListenerPrx.checkedCast( adapter.addWithUUID( myListener) )
    plant = argo.TickerPlantPrx.checkedCast( communicator.stringToProxy('plant'))
    plant.subscribe( prx )
    communicator.waitForShutdown()
    




    

