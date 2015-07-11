#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"

#include "Foo.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class MyFoo : public argo::Foo {
  std::string doit(const ::Ice::Current&) {
    cout << "Woohoo doit has been I've been called" << endl;
    return "doit from cpp";
  };

  std::string doitAgain(const ::Ice::Current&) {
    cout << "Woohoo doitAgain has been called" << endl;
    return "doitAgain from cpp";
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
