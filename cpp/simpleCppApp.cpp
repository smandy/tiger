#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"

#include "Foo.h"
#include <iostream>
#include <memory>

using namespace std;

class MyFoo : public argo::Foo {
  void doit(const ::Ice::Current&) {
    cout << "Woohoo I've been called" << endl;
  };

  void doitAgain(const ::Ice::Current&) {
    cout << "Woohoo I've been called" << endl;
  };
};

int main(int argc, char *argv[]) {
  cout << "Init ice" << endl;
  auto comm = Ice::initialize( argc, argv);
  
  // TODO get adapter name
  cout << "Create adapter" << endl;
  auto adapter = comm->createObjectAdapter( "SimpleCppApp");

  cout << "Create Servant" << endl;
  auto myHello = new MyFoo; //std::make_unique<MyFoo>();
  cout << "Add Servant" << endl;
  adapter->add(myHello, comm->stringToIdentity("foo") );
  
  cout << "Activate adapter" << endl;
  adapter->activate();

  cout << "Wait for shutdown" << endl;
  comm->waitForShutdown();
  cout << "Destroy communicator" << endl;
  
  adapter->destroy();
  comm->destroy();
};
