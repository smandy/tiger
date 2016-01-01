// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>

#include <Hello.h>
#include <Discovery.h>

using namespace std;
using namespace Demo;

class DiscoverReplyI : public DiscoverReply, public IceUtil::Monitor<IceUtil::Mutex>
{
    IceUtil::Monitor<IceUtil::Mutex> monitor;
public:
  
    virtual void
    reply(const Ice::ObjectPrx& obj, const Ice::Current&)
    {
        Lock sync(monitor);
        if(!_obj) {
            _obj = obj;
        }
        monitor.notify();
    }

    Ice::ObjectPrx
    waitReply(const IceUtil::Time& timeout)
    {
        Lock sync(monitor);
        IceUtil::Time end = IceUtil::Time::now() + timeout;
        while(!_obj) {
            IceUtil::Time delay = end - IceUtil::Time::now();
            if(delay > IceUtil::Time::seconds(0))
                {
                    monitor.timedWait(delay);
                }
            else
                {
                    break;
                }
        }
        return _obj;
    }

private:

    Ice::ObjectPrx _obj;
};
typedef IceUtil::Handle<DiscoverReplyI> DiscoverReplyIPtr;

class HelloClient : public Ice::Application
{
public:

    virtual int run(int, char*[]);

private:

    void menu();
};

int
main(int argc, char* argv[])
{
    HelloClient app;
    return app.main(argc, argv, "config.client");
}

int
HelloClient::run(int argc, char* argv[])
{
    Ice::StringSeq args = Ice::argsToStringSeq(argc, argv);
    args = communicator()->getProperties()->parseCommandLineOptions("Discover", args);

    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("DiscoverReply");
    DiscoverReplyIPtr replyI = new DiscoverReplyI;
    DiscoverReplyPrx reply = DiscoverReplyPrx::uncheckedCast(adapter->addWithUUID(replyI));
    adapter->activate();

    DiscoverPrx discover = DiscoverPrx::uncheckedCast(
                                                      communicator()->propertyToProxy("Discover.Proxy")->ice_datagram());

    std::cout << "Calling lookup with " << reply << std::endl;
    discover->lookup(reply);

    Ice::ObjectPrx base = replyI->waitReply(IceUtil::Time::seconds(2));
    
    if(!base) {
        cerr << argv[0] << ": no replies" << endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Got reply " << base << std::endl;
    };
    
    HelloPrx hello = HelloPrx::uncheckedCast(base);
    if(!hello)
        {
            cerr << argv[0] << ": invalid reply" << endl;
            return EXIT_FAILURE;
        }


    for (int i = 0;i<10;++i) {
        auto s = hello->sayHello("Andy");

        std::cout << "Received " << s << std::endl;
    }

    return EXIT_SUCCESS;
}
