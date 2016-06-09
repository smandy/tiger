import Ice

Ice.loadSlice('../slice/SimpleService.ice')

communicator = Ice.initialize( [ '--Ice.Config=discovery.properties'])



