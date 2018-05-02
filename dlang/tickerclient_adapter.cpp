#include "Ticker.h"
#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include <iostream>
#include <memory>
#include <string>
#include "wrapped_string.h"
#include "wrapped_sequence.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

using namespace std;
using namespace Ice;

struct DListener {
    void onTick( WrappedVector<::argo::Tick> ticks );
};

struct MyListener : public ::argo::TickListener {
    DListener* impl;

    MyListener( DListener* _impl) : impl(_impl) {}
    
    void onTick(::argo::TickSeq(seq), const ::Ice::Current&) {
        {
        ptime t = microsec_clock::universal_time();
        std::cout << "Ontick " << to_iso_extended_string(t) << std::endl;
        }
        impl->onTick( wrap(seq) );
        {
        ptime t = microsec_clock::universal_time();
        std::cout << "Ontick completed" << to_iso_extended_string(t) << std::endl;
        }
    }
    
    void onImage(::argo::TickImage, const ::Ice::Current&) {
        std::cout << "Todo onimage!" << std::endl;
    }
};

struct DAdapter {
  CommunicatorPtr comm;
  ObjectAdapterPtr adapter;

public:
    DAdapter(int argc, char **argv, DListener *iface)
      : comm(Ice::initialize(argc, argv)),
        adapter(comm->createObjectAdapter("SimpleDApp")) {
    std::cout << "In ctor" << std::endl;
    auto ident = adapter->add(std::make_shared<MyListener>(iface), Ice::stringToIdentity(Ice::generateUUID()));
    std::cout << "ident is " << *ident << std::endl;
    auto prx = Ice::checkedCast<argo::TickerPlantPrx>( comm->stringToProxy("plant"));
    std::cout << "Prx is " << prx << std::endl;
    adapter->activate();
    if (prx!= nullptr) {
        prx->sayHello();
        prx->subscribe(Ice::checkedCast<argo::TickListenerPrx>(ident));
    }
    //MyListener foo(iface);
  }

  void run();

  ~DAdapter() {
    std::cout << "In dtor" << std::endl;
    adapter->destroy();
    comm->destroy();
  }
};

void DAdapter::run() {
  std::cout << "Runnign - waiting for shutdown" << std::endl;
  comm->waitForShutdown();
  std::cout << "Woot I am the run method" << std::endl;
}

DAdapter *createInstance(size_t argc, char **argv, DListener* iface) {
  return new DAdapter(argc, argv, iface);
}

void deleteInstance(DAdapter *d) { delete d; }
