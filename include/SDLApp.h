#ifndef SDL_APP_H
#define SDL_APP_H

// Third-Party Library
#include <SDL.h>

class SDLApp
{
private:
   // Pointer to our SDL Window
   SDL_Window* m_window = nullptr;
   // Pointer to our SDL Renderer
   SDL_Renderer* m_renderer = nullptr;

public:
   // Constructor
   SDLApp(char* title, int x, int y, int w, int h);

   // Destructor
   ~SDLApp();
};

#endif // !SDL_APP_H
