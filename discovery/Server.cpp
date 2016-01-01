#include <Ice/Ice.h>

#include <Hello.h>

using namespace std;
using namespace Demo;

class HelloI : public Hello
{
public:

  virtual std::string sayHello(const std::string& name,const Ice::Current&)
    {
      //cout << "Hello World!" << endl;
        std::ostringstream oss;
        oss << "Hello " << name << " !!!";
        std::cout << oss.str() << std::endl;
        return oss.str();
    }
};

int main(int argc, char *argv[]) {
    auto communicator = Ice::initialize( argc, argv);
    
    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("Hello");
    Ice::ObjectPrx hello = adapter->add(new HelloI, communicator->stringToIdentity("hello"));
    adapter->activate();
    communicator->waitForShutdown();
    return EXIT_SUCCESS;
}
