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
}

void SDLApp::EventCallback()
{
   //(1) Handle Input
   SDL_Event event;

   // Capture mouse positions
   int mouseX;
   int mouseY;
   Uint32 buttons;
   buttons = SDL_GetMouseState(&mouseX, &mouseY);

   // Start our event loop
   while (SDL_PollEvent(&event))
   {
      // Handle each specific event
      if (event.type == SDL_QUIT)
      {
         m_gameIsRunning = false;
      }
      // Detect collision from our two shapes if mouse button is pressed
      if (event.button.button == SDL_BUTTON_LEFT)
      {
         // Since object2 is the one we're moving around, we'll work with it!
         if (object2.IsColliding(object1))
         {
            std::cout << "Is colliding\n";
         }
         else
         {
            std::cout << "Not colliding\n";
         }
      }
   }
}

void SDLApp::RenderCallback()
{
   // (2) Handle Updates

   // (3) Clear and Draw the Screen
   // Set a color before clearing: set the background color
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
   // Gives us a clear "canvas"
   SDL_RenderClear(renderer);

   // Do our drawing
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

   // Set draw positions and sizes
   object1.Draw(50, 50, 100, 100);
   object2.Draw(mouseX, mouseY, 100, 100);

   // Render our objects
   object1.Render(renderer);
   object2.Render(renderer);

   // Finally show what we've drawn
   SDL_RenderPresent(renderer);

   /**
   * This is how many milliseconds we want to slowdown the program
   */
   SDL_Delay(100);
}

void SDLApp::RunLoop()
{
   while (m_gameIsRunning)
   {
      EventCallback();
      RenderCallback();
   }
   
}
