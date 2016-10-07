
#!/usr/bin/env python

import Ice

if __name__=='__main__':
    communicator = Ice.initialize([])
    adapter = communicator.createObjectAdapterWithEndpoints("MyAdapter",'tcp')
    
