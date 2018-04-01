#include "Ticker.h"
#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include <iostream>
#include <memory>
#include <string>
#include "wrapped_string.h"
#include "wrapped_sequence.h"

using namespace std;
using namespace Ice;

//enum TickDirection {ZERO, UP , DOWN};
// struct DTick {
//     long symbol;
//     double bidPx;
//     double askPx;
//     TickDirection bidDirection;
//     TickDirection askDirection;
// };


namespace argo {
    struct DListener {
        void onTick( WrappedVector<::argo::Tick> ticks );
    };
}

struct MyListener : public ::argo::TickListener {
    argo::DListener* impl;

    MyListener( argo::DListener* _impl) : impl(_impl) {}
    
    void onTick(::argo::TickSeq(seq), const ::Ice::Current&) {
        impl->onTick( wrap(seq) );
    }
    
    void onImage(::argo::TickImage, const ::Ice::Current&) {
        std::cout << "Todo onimage!" << std::endl;
    }
};


// class MyFoo : public argo::Foo {
//   FooInterface *impl;
// public:
//   MyFoo(FooInterface *ptr) : impl(ptr) {}
//   void doitAsync(::std::function<void(const ::std::string &)> cb,
//                  ::std::function<void(::std::exception_ptr)>,
//                  const ::Ice::Current &) {
//       std::cout << "impl->doit " << std::string(impl->doit()) << std::endl;
//     cb(impl->doit());
//   };
//   void doitAgainAsync(::std::function<void(const ::std::string &)> cb,
//                       ::std::function<void(::std::exception_ptr)>,
//                       const ::Ice::Current &) {
//     cb(impl->doitAgain());
//   }
// };

struct DAdapter {
  CommunicatorPtr comm;
  ObjectAdapterPtr adapter;
    //FooInterface* iface;

public:
    DAdapter(int argc, char **argv, argo::DListener *iface)
      : comm(Ice::initialize(argc, argv)),
        adapter(comm->createObjectAdapter("SimpleDApp")) {
    std::cout << "In ctor" << std::endl;
    adapter->add(std::make_shared<MyListener>(iface), Ice::stringToIdentity("foo"));
    adapter->activate();
    MyListener foo(nullptr);
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

DAdapter *createInstance(size_t argc, char **argv, argo::DListener* iface) {
  return new DAdapter(argc, argv, iface);
}

void deleteInstance(DAdapter *d) { delete d; }
