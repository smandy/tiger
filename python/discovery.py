import Ice

Ice.loadSlice('../slice/Foo.ice')
import argo

communicator = Ice.initialize( [ '--Ice.Config=locator.properties'])
cppPrx = communicator.stringToProxy('foo@SimpleCppApp')
cppFoo = argo.FooPrx.checkedCast(cppPrx)

print "Doit      -> %s" % cppFoo.doit()
print "DoitAgain -> %s" % cppFoo.doitAgain()

pyPrx = communicator.stringToProxy('foo@SimpleApp')
pyFoo = argo.FooPrx.checkedCast(pyPrx)

print "Doit      -> %s" % pyFoo.doit()
print "DoitAgain -> %s" % pyFoo.doitAgain()

scalaPrx = communicator.stringToProxy('foo@SimpleJavaApp')
scalaFoo = argo.FooPrx.checkedCast(scalaPrx).ice_timeout(5000)

print "Doit      -> %s" % scalaFoo.begin_doit()
print "DoitAgain -> %s" % scalaFoo.begin_doitAgain()


proxies = [ cppFoo, pyFoo, scalaFoo ]

# Phase 1 async invocations. Relatively cool
invocations = []
invocations += [ (x.end_doit      , x.begin_doit() )      for x in proxies ]
invocations += [ (x.end_doitAgain , x.begin_doitAgain() ) for x in proxies ]

for getter, invocation in invocations:
    print "%s -> %s" % (getter, getter(invocation))

import functools
from pprint import pprint as pp
results = []

# Phase 2 async - using receive callbacks so we can do funky batch-invocation like stuff.

# Collector maybe a re-use candidate.... *maybe*
class Collector:
    def __init__(self, onComplete):
        self.methods = {}
        self.allMethods = {}
        self.counter = 0
        self.onComplete = onComplete

    def makeCaller(self, f, argx):
        myId = self.counter
        def ret(*argy):
            #print "Woot"
            del self.methods[myId]
            newArgs = argx + argy
            r2 = f( *newArgs )
            if not(self.methods):
                self.onComplete()
            #print self.methods
            return r2
        return ret
        
    def curry( self, iranu, uvavu, *argx ):
        ret = {
            '_response' : self.makeCaller( iranu, argx),
            '_ex'       : self.makeCaller( uvavu, argx)
            }
        self.methods[self.counter] = ret
        self.allMethods[self.counter] = ret
        self.counter += 1
        return ret

# Beware - all of these are called from an ice thread.
def myExcept(*args):
    print "Exception %s" % args
    x
def receive( prx, method, resp):
    print "Woot %s %s %s" % (prx, method, resp)
    results.append( (prx, method, resp) )

def myComplete():
    print "All Done"
    pp(results)
    communicator.shutdown()

col   = Collector(myComplete)
curry = col.curry

for x in proxies:
    x.begin_doit(      **curry( receive, myExcept, x, 'doit'      ) )
    x.begin_doitAgain( **curry( receive, myExcept, x, 'doitAgain' ) )
