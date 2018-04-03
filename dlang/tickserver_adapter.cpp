#include "Ice/Ice.h"
#include "Ticker.h"

struct TickReceiver : public argo::TickerPlant {
  Ice::CommunicatorPtr comm;
  Ice::ObjectAdapterPtr adapter;

  void join();
  void stop();

  TickReceiver(Ice::CommunicatorPtr _comm, Ice::ObjectAdapterPtr _adapter)
      : comm(_comm), adapter(_adapter) {}

  virtual void subscribe(::std::shared_ptr<::argo::TickListenerPrx>,
                         const ::Ice::Current &);
  virtual void subscribeWithIdent(::Ice::Identity, const ::Ice::Current &);
  virtual ::std::string sayHello(const ::Ice::Current &);
};

void TickReceiver::subscribe(::std::shared_ptr<::argo::TickListenerPrx>,
                             const ::Ice::Current &) {}
void TickReceiver::subscribeWithIdent(::Ice::Identity, const ::Ice::Current &) {
}
std::string TickReceiver::sayHello(const ::Ice::Current &) { return "woot"; }

void TickReceiver::join() { comm->waitForShutdown(); }

void TickReceiver::stop() { comm->shutdown(); }

TickReceiver *createInstance(size_t argc, char **argv) {
  int x = (int)argc;
  auto comm = Ice::initialize(x, argv);
  auto adapter = comm->createObjectAdapter("TickServer"); // TODO - param
  std::cout << "TickReceiver constructor" << std::endl;
  // Adapter should keep me alive
  auto receiver = std::make_shared<TickReceiver>(comm, adapter);
  adapter->add(receiver, Ice::stringToIdentity("server"));
  adapter->activate();
};
