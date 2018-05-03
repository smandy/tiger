#include "Ice/Ice.h"
#include "Foo.h"
#include "Ticker.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

template<typename T>
struct TR;

struct MyListener : public ::argo::TickListener {
    void onTick(::argo::TickSeq seq, const ::Ice::Current&) {
        {
            ptime t = microsec_clock::universal_time();
            std::cout << "Ontick " << to_iso_extended_string(t) << std::endl;
        }
        for( auto& t : seq) {
            std::cout << t.symbol << "," << t.bidPx << "," << t.askPx << std::endl;
        };
    }
    
    void onImage(::argo::TickImage, const ::Ice::Current&) {
    }
};

int main(int argc, char *argv[]) {
    auto communicator = Ice::initialize(argc, argv);
    auto adapter = communicator->createObjectAdapterWithEndpoints("","tcp");
    std::cout << "Adnapter " << std::endl;
    auto ident = adapter->addWithUUID(std::make_shared<MyListener>() );
    auto listener = Ice::checkedCast<argo::TickListenerPrx>(ident);
    auto prx = Ice::checkedCast<argo::TickerPlantPrx>(communicator->stringToProxy("plant"));
    if (prx!= nullptr) {
        //prx->sayHello();
        prx->subscribe(listener);
    }
    adapter->activate();
    communicator->waitForShutdown();
    adapter->destroy();
    communicator->destroy();
}
