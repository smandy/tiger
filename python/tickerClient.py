

import Ice
import sys

from common import getUUID

Ice.loadSlice('../slice/Ticker.ice')

import argo

class MyListener(argo.TickListener):
    def onTick(self, tix, current):
        print "onTick %s" % tix

if __name__=='__main__':
    communicator = Ice.initialize(['--Ice.Config=tickerplant.properties'] )
    adapter = communicator.createObjectAdapterWithEndpoints( getUUID(), "tcp" )
    adapter.activate()
    myListener = MyListener()
    prx = argo.TickListenerPrx.checkedCast( adapter.addWithUUID( myListener) )
    plant = argo.TickerPlantPrx.checkedCast( communicator.stringToProxy('plant'))
    plant.subscribe( prx )
    communicator.waitForShutdown()
    




    

