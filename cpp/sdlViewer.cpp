#include <iostream>
#include <stdlib.h> //Needed for "exit" function

// Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Ice/Ice.h"
#include "SDL_ttf.h"
#include "Ticker.h"
#include <SDL.h>
#include <iostream>
#include <math.h>
#include <memory>
#include <mutex>
#include <spdlog/spdlog.h>

using namespace std;

using loggerType = std::shared_ptr<spdlog::logger>;

uint32_t renderCallback(uint32_t currentInterval, void *p) {
  SDL_Event event;
  SDL_UserEvent userevent;
  /* In this example, our callback pushes a function
  into the queue, and causes our callback to be called again at the
  same interval: */

  mutex m;

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = 0;
  userevent.data2 = 0;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return (currentInterval);
}

class SDLViewer : public argo::TickListener {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  ::Ice::CommunicatorPtr communicator;
  loggerType log;

  SDL_Color WHITE{255, 255, 255, 255};
  SDL_Color RED{255, 0, 0, 255};
  SDL_Color GREEN{0, 255, 0, 255};

public:
  int width, height;
  std::map<std::string, argo::Tick> ticks;
  std::mutex m;

  virtual void onTick(const ::argo::TickSeq &xs,
                      const ::Ice::Current & = ::Ice::Current()){
      // cout << "OnTick\n";
      {lock_guard<mutex>{m};
  for (auto &x : xs) { // XXX:
    ticks[x.symbol] = x;
  };
}
}
;

virtual void onImage(const ::argo::TickImage &img,
                     const ::Ice::Current & = ::Ice::Current()) {
  // cout << "OnImage\n";
  {
    lock_guard<mutex>{m};
    // TODO: icks.clear();
    for (auto &seq : img) {
      for (auto &p : seq) {
        ticks[p.symbol] = p;
      };
    };
  }
}

SDLViewer(::Ice::CommunicatorPtr _communicator, uint32_t _width,
          uint32_t _height)
    : communicator(_communicator), width(_width), height(_height),
      log(spdlog::get("log")) {
  // Initialize SDL
  // ==========================================================
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    // Something failed, print error and exit.
    std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    exit(1);
  }

  // Create and init the window
  // ==========================================================
  window = SDL_CreateWindow("Server", 20, 20, width, height, 0);
  if (window == nullptr) {
    std::cout << "Failed to create window : " << SDL_GetError();
    exit(1);
  }

  // Create and init the renderer
  // ==========================================================
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cout << "Failed to create renderer : " << SDL_GetError();
    exit(1);
  }

  TTF_Init();
  font = TTF_OpenFont(
      "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf", 12);
  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
    exit(1);
    std::cout << "Have set font " << font << std::endl;
  }

  // Render something
  // ==========================================================
  SDL_RenderSetLogicalSize(renderer, width, height);
  auto x = SDL_AddTimer(60, renderCallback, nullptr);

  auto adapter = communicator->createObjectAdapterWithEndpoints("", "tcp");
  adapter->activate();
  auto myPrx = argo::TickListenerPrx::uncheckedCast(adapter->addWithUUID(this));

  auto tmpPrx = communicator->stringToProxy("plant");

  std::cout << "Ping\n";
  tmpPrx->ice_ping();
  std::cout << "Pong\n";

  std::cout << "Proxy is " << communicator->proxyToString(tmpPrx) << std::endl;
  auto plant = argo::TickerPlantPrx::checkedCast(tmpPrx);

  std::cout << "Plant is " << plant << std::endl;

  plant->subscribe(myPrx);
};

SDL_Color &colorForDirection(argo::TickDirection dir) {
  switch (dir) {
  case argo::TickDirection::ZERO:
    return WHITE;
  case argo::TickDirection::UP:
    return GREEN;
  case argo::TickDirection::DOWN:
    return RED;
  default:
    log->error("Unmapped direction {}", dir);
  };
};

void render() {
  // TD<decltype(TTF_OpenFont("foo", 10))> fooType;
  // auto ctx = reinterpret_cast<Context *>(p);
  // std::cout << "TImer x=" << x << " y=" << y << "\n";
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
  SDL_RenderClear(renderer);

  SDL_Color c{255, 255, 255, 255};

  std::ostringstream oss;
  // oss << "Woot " << ticks.size() << std::endl;

  {
    lock_guard<mutex>{m};
    int j = 20;
    for (auto &p : ticks) {
      auto bidColor = colorForDirection(p.second.bidDirection);
      auto askColor = colorForDirection(p.second.askDirection);
      text(20, j, p.second.symbol, WHITE);
      text(200, j, std::to_string(p.second.bidPx), bidColor);
      text(400, j, std::to_string(p.second.askPx), askColor);
      j += 20;
    }
  }
  // TODO - update ticks
  SDL_RenderPresent(renderer);
};

void text(int32_t x, int32_t y, std::string s, SDL_Color c) {
  auto surf2 = TTF_RenderText_Solid(font, s.c_str(), c);
  if (!surf2) {
    printf("TTF_RenderText: %s\n", TTF_GetError());
  }

  auto texture = SDL_CreateTextureFromSurface(renderer, surf2);
  if (!texture) {
    printf("SDL_CreateTexturefromsurface: %s\n", SDL_GetError());
  };

  auto h = surf2->h;
  auto w = surf2->w;

  SDL_FreeSurface(surf2);
  SDL_Rect dest = {x, y, w, h};
  SDL_RenderCopy(renderer, texture, nullptr, &dest);
  SDL_DestroyTexture(texture);
};

void mainLoop() {
  SDL_Event event;
  bool done = false;

  while (!done) {
    while (SDL_PollEvent(&event)) {
      auto tix = SDL_GetTicks();
      switch (event.type) {
      case SDL_KEYDOWN: {
        if (!event.key.repeat) {
          switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: {
            done = 1;
            break;
          }
          case SDLK_LEFT: {
            // paddleState = PaddleState::MOVING_LEFT;
            break;
          }
          case SDLK_RIGHT: {
            // paddleState = PaddleState::MOVING_RIGHT;
            break;
          }
          }
        }
        break;
      };
      case SDL_KEYUP: {
        if (!event.key.repeat) {
          switch (event.key.keysym.sym) {
          case SDLK_LEFT: {
            // paddleState = PaddleState::STATIONARY;
            break;
          }
          case SDLK_RIGHT: {
            // paddleState = PaddleState::STATIONARY;
            break;
          }
          }
        };
        break;
      };
      case SDL_USEREVENT: {
        /* and now we can call the function we wanted to call in the timer but
         * couldn't because of the multithreading problems */
        // auto p = (void (*)(void *))event.user.data1;
        // p(event.user.data2);
        // updateState();
        render();
        break;
      }
      case SDL_QUIT: {
        done = true;
        break;
      }
      }
      /* ... */
    }
  }
}
}
;

int main(int argc, char **argv) {
  int done;
  auto communicator = Ice::initialize(argc, argv);
  auto log =
      spdlog::rotating_logger_mt("sdlLog", "/tmp/sdlLog", 1048576 * 5, 3);
  SDLViewer app(communicator, 800, 600);
  // MyHandler eventHandler(app.renderer, 2.0f, 0.98);
  log->info("Enter mainloop\n");
  app.mainLoop();
  log->info("Exit mainloop\n");
  return 0; // This line is never reached
}
