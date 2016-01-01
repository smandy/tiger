#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>

#include <Hello.h>

using namespace std;
using namespace Demo;

int main(int argc, char* argv[]) {
    
    auto communicator = Ice::initialize( argc, argv);
    
    HelloPrx hello = HelloPrx::checkedCast( communicator->stringToProxy("hello"));
    if(!hello) {
        cerr << argv[0] << ": invalid reply" << endl;
        return EXIT_FAILURE;
    }

    for (int i = 0;i<1;++i) {
        auto s = hello->sayHello("Andy");
        std::cout << "Received " << s << std::endl;
    }

    communicator->shutdown();
    
    return EXIT_SUCCESS;
}
