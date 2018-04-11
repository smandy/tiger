#include "Ice/Ice.h"
#include "Ticker.h"

#include <set>
#include <thread>
#include <atomic>

template <typename T> struct TR;

struct TickReceiver : public argo::TickerPlant {
  Ice::CommunicatorPtr comm;
  Ice::ObjectAdapterPtr adapter;
  std::mutex m;
  using lock_type = std::lock_guard<std::mutex>;
  std::set<std::shared_ptr<argo::TickListenerPrx>> listeners;

  void join();
  void stop();

  std::thread t;

    std::atomic<bool> running;

  TickReceiver(Ice::CommunicatorPtr _comm, Ice::ObjectAdapterPtr _adapter)
      : comm(_comm), adapter(_adapter), m{}, t{[&]() {
          while (running.load()) {
            {
              lock_type l{m};
              // std::cout << "Boop here we go have " << listeners.size()
              //           << " Listeners " << std::endl;
              for (auto &listener : listeners) {
                // std::cout << "Calling proxy" << std::endl;
                std::vector<::argo::Tick> myTicks{
                    {666, 101.0, 102.0, ::argo::TickDirection::UP,
                            ::argo::TickDirection::DOWN},
                    {1024, 103.0, 104.0, ::argo::TickDirection::DOWN,
                            ::argo::TickDirection::UP},
                        
                        };
                auto fut = listener->onTickAsync(
                    myTicks, []() { std::cout << "Bleep" << std::endl; },
                    [&](std::exception_ptr ex) {
                      try {
                        if (ex) {
                          std::rethrow_exception(ex);
                        }
                      } catch (const std::exception &e) {
                        std::cout << "Caught exception \"" << e.what()
                                  << "\"\n";
                      }
                      //std::cout << "Exception" << ex.what() << std::endl;
                      // DODGY - are we deadlocking? shoudn't be we're on the
                      // client thredpool at this stage
                      {
                        lock_type x{m};
                        std::cout << "Removing listener" << std::endl;
                        listeners.erase(listener);
                      }
                    });
              }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
          }
        }} {
    std::cout << "TickReceiver ctor" << std::endl;
    std::cout << "Comm is " << comm << std::endl;
  }

  virtual void subscribe(::std::shared_ptr<::argo::TickListenerPrx>,
                         const ::Ice::Current &);
  virtual void subscribeWithIdent(::Ice::Identity, const ::Ice::Current &);
  virtual ::std::string sayHello(const ::Ice::Current &);
};

void TickReceiver::subscribe(
    ::std::shared_ptr<::argo::TickListenerPrx> listener,
    const ::Ice::Current &) {
  std::cout << "tickserver_adapter subscribing" << std::endl;

  {
    lock_type l{m};
    listeners.emplace(std::move(listener));
  }
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

void TickReceiver::stop() { running.store(false);comm->shutdown(); }

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
