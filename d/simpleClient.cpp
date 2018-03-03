#include "Ice/Ice.h"
#include "Foo.h"

template<typename T>
struct TR;

int main(int argc, char *argv[]) {
    auto communicator = Ice::initialize();
    auto prx = Ice::uncheckedCast<::argo::FooPrx>(communicator->propertyToProxy("SimpleDApp.Proxy"));

    std::cout << "Doit->" << prx->doit() << std::endl;
    std::cout << "DoitAgain->" << prx->doitAgain() << std::endl;
}
