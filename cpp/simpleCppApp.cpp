#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include "Foo.h"
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;
using namespace std;

class MyFoo : public argo::Foo {
    void addAsync(int a, int b, ::std::function<void(int)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {
        std::cout << "Adding " << a << " and " << b  << std::endl;
        cb( a + b );
    }
    
    void doitAsync(::std::function<void(const ::std::string&)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&)  {

        std::ostringstream ss;
        ptime t = microsec_clock::universal_time();
        ss << "hello from C++!! " << to_iso_extended_string(t) << std::endl;
        cb(ss.str());
    }

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
