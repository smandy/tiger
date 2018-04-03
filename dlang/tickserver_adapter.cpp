#include "Ice/Ice.h"
#include "Ticker.h"

struct TickReceiver : public argo::TickerPlant {
  Ice::CommunicatorPtr comm;
  Ice::ObjectAdapterPtr adapter;

  void join();
  void stop();

  TickReceiver(Ice::CommunicatorPtr _comm, Ice::ObjectAdapterPtr _adapter)
      : comm(_comm), adapter(_adapter) {
      std::cout << "TickReceiver ctor" << std::endl;
      std::cout << "Comm is " << comm << std::endl;
  }

  virtual void subscribe(::std::shared_ptr<::argo::TickListenerPrx>,
                         const ::Ice::Current &);
  virtual void subscribeWithIdent(::Ice::Identity, const ::Ice::Current &);
  virtual ::std::string sayHello(const ::Ice::Current &);
};

void TickReceiver::subscribe(::std::shared_ptr<::argo::TickListenerPrx>,
                             const ::Ice::Current &) {
    std::cout << "tickserver_adapter subscribing" << std::endl;
    std::vector<::argo::Tick> myTicks { { 666, 101.0,102.0,
                ::argo::TickDirection::UP, ::argo::TickDirection::DOWN } };
    
}
void TickReceiver::subscribeWithIdent(::Ice::Identity, const ::Ice::Current &) {
    std::cout << "tickserver_adapter subscribe with ident" << std::endl;
}
std::string TickReceiver::sayHello(const ::Ice::Current &) {
    std::cout << "tickserver_adapter sayhello" << std::endl;
    return "woot";
}

void TickReceiver::join() {
    std::cout << "cpp about to join comm is " << comm << std::endl;
    comm->waitForShutdown();
    std::cout << "cpp joined" << std::endl;
}

void TickReceiver::stop() { comm->shutdown(); }

TickReceiver *createInstance(size_t argc, char **argv) {
    std::cout << "Create instance" << std::endl;
  int x = (int)argc;
  auto comm = Ice::initialize(x, argv);
  auto adapter = comm->createObjectAdapter("TickServer"); // TODO - param
  std::cout << "TickReceiver constructor" << std::endl;
  // Adapter should keep me alive
  auto receiver = std::make_shared<TickReceiver>(comm, adapter);
  adapter->add(receiver, Ice::stringToIdentity("plant"));
  adapter->activate();
  return receiver.get();
};
