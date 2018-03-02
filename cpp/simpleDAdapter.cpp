#include "Foo.h"
#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;
using namespace Ice;

template <int N = 128> struct WrappedString {

  char buf[N];

  operator std::string() { return std::string(buf); };
};

template <int N = 128> struct FooInterface {
  WrappedString<N> doit();
  WrappedString<N> doitAgain();
};

class MyFoo : public argo::Foo {
  FooInterface<> *impl;

public:
  MyFoo(FooInterface<> *ptr) : impl(ptr) {}

  void doitAsync(::std::function<void(const ::std::string &)> cb,
                 ::std::function<void(::std::exception_ptr)>,
                 const ::Ice::Current &) {
    cb(impl->doit());
  };

  void doitAgainAsync(::std::function<void(const ::std::string &)> cb,
                      ::std::function<void(::std::exception_ptr)>,
                      const ::Ice::Current &) {
    cb(impl->doitAgain());
  }
};

struct DAdapter {
  CommunicatorPtr comm;
  ObjectAdapterPtr adapter;
  FooInterface<> *iface;

public:
  DAdapter(int argc, char ** argv, FooInterface<> *iface)
      : comm(Ice::initialize(argc, argv)),
        adapter(comm->createObjectAdapter("SimpleDApp")) {
    std::cout << "In ctor" << std::endl;
    adapter->add(std::make_shared<MyFoo>(iface), Ice::stringToIdentity("foo"));
  }

  void run() {
      comm->waitForShutdown();
      std::cout << "Woot I am the run method" << std::endl;
  }

  ~DAdapter() {
    std::cout << "In dtor" << std::endl;
    adapter->destroy();
    comm->destroy();
  }
};

DAdapter *createInstance(int argc, char **argv, FooInterface<> *iface) {
  return new DAdapter(argc, argv, iface);
};

void deleteInstance(DAdapter *d) { delete d; };

// template <typename T>
// struct TR;

// int main(int argc, char *argv[]) {
//   cout << "Init ice" << endl;
//   auto comm = Ice::initialize(argc, argv);

//   // TODO get adapter name
//   cout << "Create adapter" << endl;
//   auto adapter = comm->createObjectAdapter("SimpleCppApp");

//   //TR<decltype(adapter)> myType;

//   FooInterface<128> interface; // This is a d guy!

//   cout << "Create Servant" << endl;
//   // auto myHello = new MyFoo; //std::make_unique<MyFoo>();
//   auto myHello = std::make_shared<MyFoo>(&interface);
//   cout << "Add Servant" << endl;
//   adapter->add(myHello, Ice::stringToIdentity("foo"));

//   cout << "Activate adapter" << endl;
//   adapter->activate();

//   cout << "Wait for shutdown" << endl;
//   comm->waitForShutdown();
//   cout << "Destroy communicator" << endl;

//   adapter->destroy();

//   comm->destroy();
// }
