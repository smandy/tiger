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

    void destroy_communicator();
    
    DAdapter(const std::string &str_proxy) 
        : comm {Ice::initialize() },
          prx {Ice::uncheckedCast<::argo::FooPrx>(comm->stringToProxy(str_proxy))}
    {
        std::cout << "str_proxy " << str_proxy << std::endl;
        std::cout << "prx is " << prx << std::endl;
    }
};

WrappedString DAdapter::doit() {
    return wrap(prx->doit());
};

WrappedString DAdapter::doitAgain() {
    return wrap(prx->doitAgain());
};

void DAdapter::destroy_communicator() {
    std::cout << "Destroying" << std::endl;
    comm->destroy();
};

DAdapter *createInstance(char* str_proxy) {
    std::cout << "Create instance " << std::endl;
    std::string s(str_proxy);
    std::cout << "Prx is " << s << std::endl;
    return new DAdapter(s);
}

void deleteInstance(DAdapter *d) {
    std::cout << "Delete instance instance " << std::endl;
    d->destroy_communicator();
    delete d;
}
