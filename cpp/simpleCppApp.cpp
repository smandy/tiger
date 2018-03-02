#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include "Foo.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;


class MyFoo : public argo::Foo {
    void doitAsync(::std::function<void(const ::std::string&)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&)  {
        cb("Hello from ice");
    };

    void doitAgainAsync(::std::function<void(const ::std::string&)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {
        cb("doit again from cpp");
    }
};

int main(int argc, char *argv[]) {
  cout << "Init ice" << endl;
  auto comm = Ice::initialize( argc, argv);
  
  // TODO get adapter name
  cout << "Create adapter" << endl;
  auto adapter = comm->createObjectAdapter( "SimpleCppApp");

  cout << "Create Servant" << endl;
  //auto myHello = new MyFoo; //std::make_unique<MyFoo>();
  auto myHello = std::make_shared<MyFoo>();
  cout << "Add Servant" << endl;
  adapter->add(myHello, Ice::stringToIdentity("foo") );
  
  cout << "Activate adapter" << endl;
  adapter->activate();

  cout << "Wait for shutdown" << endl;
  comm->waitForShutdown();
  cout << "Destroy communicator" << endl;
  
  adapter->destroy();

  comm->destroy();

}
