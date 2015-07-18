import uuid

def getUUID():
    return str(uuid.uuid4())

if __name__=='__main__':
    print getUUID()
