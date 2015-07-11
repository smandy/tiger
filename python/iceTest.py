
#!/usr/bin/env python

import Ice
import sys

if __name__=='__main__':
    communicator = Ice.initialize([])
    adapter = communicator.createObjectAdapterWithEndpoints("MyAdapter",'tcp')
    
