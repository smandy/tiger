#include "Foo.h"
#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include "wrapped_string.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;
using namespace Ice;

struct FooInterface {
  WrappedString doit();
  WrappedString doitAgain();
  int add(int a, int b);
};

class MyFoo : public argo::Foo {
  FooInterface *impl;

public:
  MyFoo(FooInterface *ptr) : impl(ptr) {}

  void addAsync(int a, int b, std::function<void(int)> cb,
                std::function<void(std::__exception_ptr::exception_ptr)>,
                const Ice::Current &) {
    cb(impl->add(a, b));
  }

  void doitAsync(::std::function<void(const ::std::string &)> cb,
                 ::std::function<void(::std::exception_ptr)>,
                 const ::Ice::Current &) {
    std::cout << "impl->doit " << std::string(impl->doit()) << std::endl;
    cb(impl->doit());
  }

  void doitAgainAsync(::std::function<void(const ::std::string &)> cb,
                      ::std::function<void(::std::exception_ptr)>,
                      const ::Ice::Current &) {
    cb(impl->doitAgain());
  }
};

struct DAdapter {
  CommunicatorPtr comm;
  ObjectAdapterPtr adapter;
  FooInterface *iface;

public:
  DAdapter(int argc, char **argv, FooInterface *iface)
      : comm(Ice::initialize(argc, argv)),
        adapter(comm->createObjectAdapter("SimpleDApp")) {
    std::cout << "In ctor" << std::endl;
    adapter->add(std::make_shared<MyFoo>(iface), Ice::stringToIdentity("foo"));
    adapter->activate();
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

DAdapter *createInstance(size_t argc, char **argv, FooInterface *iface) {
  return new DAdapter(argc, argv, iface);
}

void deleteInstance(DAdapter *d) { delete d; }
