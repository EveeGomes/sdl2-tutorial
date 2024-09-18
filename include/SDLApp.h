#ifndef SDL_APP_H
#define SDL_APP_H

// C++ Standard Libraries
#include <functional>

// Third-Party Library
#include <SDL.h>

class SDLApp
{
private:
   // Pointer to our SDL Window
   SDL_Window* m_window = nullptr;
   // Pointer to our SDL Renderer
   SDL_Renderer* m_renderer = nullptr;
   // Infinite loop for our application
   bool m_gameIsRunning = true;

   // Store our callback functions (std::function let us work with function pointers)
   std::function<void(void)> m_RenderCallback;
   std::function<void(void)> m_EventCallback;

public:
   // Constructor
   SDLApp(const char* title, int x, int y, int w, int h);

   // Destructor
   ~SDLApp();

   // Set the event callback
   void SetEventCallback(std::function<void(void)> func);

   // Set the render callback
   void SetRenderCallback(std::function<void(void)> func);

   // Loop our application
   void RunLoop();
};

#endif // !SDL_APP_H
