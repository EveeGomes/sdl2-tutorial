#include "SDLApp.h"

// C++ Standard Libraries
#include <iostream>

SDLApp::SDLApp(char* title, int x, int y, int w, int h)
{
   /**
   * Initialize the video subsystem.
   * If it returns less than 1, then an error code will
   *  be received.
   */
   if (SDL_INIT_VIDEO < 0)
   {
      std::cout << "SDL could not be initialized: "
         << SDL_GetError();
   }
   else
   {
      std::cout << "SDL is ready to go.\n";
   }

   /**
   * Request a window to be created for our platform.
   * Add the SDL_WINDOW_OPENGL flag so it can be a window
   *  usable with an OpenGL context.
   */
   m_window = SDL_CreateWindow("C++ SDL2 Window", x, y, w, h, SDL_WINDOW_SHOWN);

   m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

SDLApp::~SDLApp()
{
   // Destroy our m_window
   SDL_DestroyWindow(m_window);
}
