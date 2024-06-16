// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>

int main(int argc, char* argv[])
{
   // Create window data type
   SDL_Window* window = nullptr;

   // Initialize window
   if (SDL_INIT_VIDEO < 0)
   {
      std::cout << "SDL could not be initialized: "
                << SDL_GetError();
   }
   else
   {
      std::cout << "SDL is ready to go.\n";
   }

   // Create the window
   window = SDL_CreateWindow("C++ SDL2 Window", 
                              20,
                              20,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);

   SDL_Delay(3000);

   SDL_DestroyWindow(window);

   SDL_Quit();

   return 0;
}