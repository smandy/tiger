import Ice

Ice.loadSlice('../slice/SimpleService.ice')
import argo

communicator = Ice.initialize( [ '--Ice.Config=discovery.properties'])



