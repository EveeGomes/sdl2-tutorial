#include "SDLApp.h"

// C++ Standard Libraries
#include <iostream>

SDLApp::SDLApp(const char* title, int x, int y, int w, int h)
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
   // Quit our SDL application
   SDL_Quit();
}

void SDLApp::SetEventCallback(std::function<void(void)> func)
{
   m_EventCallback = func;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func)
{
   m_RenderCallback = func;
}

void SDLApp::RunLoop()
{
   while (m_gameIsRunning)
   {
      // Instead of having the user worry about getting the mouse state, update them here in the API
      Uint32 buttons;
      buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

      // (1) Handle events first
      // User specifies what to do in the events callback
      m_EventCallback();

      // (2) Clear and Draw the Screen
      // Set a color before clearing: set the background color
      SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(m_renderer);

      // Do our drawing
      SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      // (3) Then, handle our rendering
      // What the user specifies to happen during the rendering stage in this callback function
      m_RenderCallback();

      // Finally show what we've drawn
      SDL_RenderPresent(m_renderer);

      // TODO: eventually set a frame cap
      SDL_Delay(100);
   }
   
}

void SDLApp::StopAppLoop()
{
   m_gameIsRunning = false;
}
