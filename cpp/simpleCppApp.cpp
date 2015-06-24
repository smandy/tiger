#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Init ice" << endl;
  auto comm = Ice::initialize( argc, argv);
  
  // TODO get adapter name

  cout << "Create adapter" << endl;
  auto adapter = comm->createObjectAdapter( "SimpleCppApp");
  cout << "Activate adapter" << endl;
  adapter->activate();

  cout << "Wait for shutdown" << endl;
  comm->waitForShutdown();
  cout << "Destroy communicator" << endl;

  adapter->destroy();
  comm->destroy();
};
