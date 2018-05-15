#include "Foo.h"
#include "Ice/Ice.h"
#include "IceUtil/IceUtil.h"
#include <iostream>
#include <memory>
#include <string>
#include "wrapped_string.h"

using namespace std;
using namespace Ice;

struct DAdapter {
    CommunicatorPtr comm;
    std::shared_ptr<::argo::FooPrx> prx;

public:
    WrappedString doit();
    WrappedString doitAgain();
    int add(int a, int b);

    void destroy_communicator();
    DAdapter(int argc, char *argv[]) 
        : comm { Ice::initialize(argc, argv) },
          prx { Ice::uncheckedCast<::argo::FooPrx>(comm->propertyToProxy("Foo"))}
    {
        //std::cout << "str_proxy " << str_proxy << std::endl;
        std::cout << "prx is " << prx << std::endl;
    }
};

WrappedString DAdapter::doit() {
    return wrap(prx->doit());
};

int DAdapter::add(int a, int b) {
    return a + b;
};


WrappedString DAdapter::doitAgain() {
    return wrap(prx->doitAgain());
};

void DAdapter::destroy_communicator() {
    std::cout << "Destroying" << std::endl;
    comm->destroy();
};

DAdapter *createInstance(int argc, char *argv[]) {
    std::cout << "Create instance " << std::endl;
    return new DAdapter(argc, argv);
}

void deleteInstance(DAdapter *d) {
    std::cout << "Delete instance instance " << std::endl;
    d->destroy_communicator();
    delete d;
}
