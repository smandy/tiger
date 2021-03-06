import Ice

Ice.loadSlice( '../slice/Foo.ice')
import argo
communicator = Ice.initialize()
fooPrx = argo.FooPrx.uncheckedCast( communicator.stringToProxy('foo:tcp -p 1099 -h ritz'))
print( [ getattr(fooPrx, x)() for x in ['doit', 'doitAgain'] ] )
communicator.destroy()
