#include <iostream>
#include <stdlib.h> //Needed for "exit" function

// Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <SDL.h>
#include "SDL_ttf.h"

#include "Ice/Ice.h"

#include "Ticker.h"

using namespace std;

uint32_t renderCallback(uint32_t currentInterval, void *p) {
  SDL_Event event;
  SDL_UserEvent userevent;
  /* In this example, our callback pushes a function
  into the queue, and causes our callback to be called again at the
  same interval: */

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = 0;
  userevent.data2 = 0;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return (currentInterval);
}

class MyTickerListener : public argo::TickListener {
    virtual void onTick(const ::argo::TickSeq&, const ::Ice::Current& = ::Ice::Current()) {
    };
    
    virtual void onImage(const ::argo::TickImage&, const ::Ice::Current& = ::Ice::Current()) {
    };
};

class SDLViewer {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  ::Ice::CommunicatorPtr communicator;
    MyTickerListener listener;

public:
  int width, height;

  SDLViewer(::Ice::CommunicatorPtr _communicator, uint32_t _width,
            uint32_t _height)
      : communicator(_communicator), width(_width), height(_height) {
    // Initialize SDL
    // ==========================================================
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      // Something failed, print error and exit.
      std::cout << " Failed to initialize SDL : " << SDL_GetError()
                << std::endl;
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
    auto x = SDL_AddTimer(200, renderCallback, nullptr);
  };

  void render() {
    // TD<decltype(TTF_OpenFont("foo", 10))> fooType;
    // auto ctx = reinterpret_cast<Context *>(p);
    // std::cout << "TImer x=" << x << " y=" << y << "\n";
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderClear(renderer);

    SDL_Color c{ 255, 255, 255, 255 };

    auto surf2 = TTF_RenderText_Solid(font, "Woot", c);
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
    SDL_Rect dest = { 20, 20, w, h };
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    SDL_DestroyTexture(texture);

    // TODO - update ticks
    SDL_RenderPresent(renderer);
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
};

int main(int argc, char **argv) {
  int done;

  auto communicator = Ice::initialize(argc, argv);

  SDLViewer app(communicator, 800, 600);
  // MyHandler eventHandler(app.renderer, 2.0f, 0.98);
  std::cout << "Enter mainloop" << std::endl;
  app.mainLoop();
  std::cout << "Exit mainloop" << std::endl;
  return 0; // This line is never reached
}
