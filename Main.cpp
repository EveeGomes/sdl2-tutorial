// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>

int main(int argc, char* argv[])
{
   // To check whether SDL is working, use if statement and call a function:
   if (SDL_INIT_VIDEO < 0)
   {
      std::cout << "SDL could not be initialized: "
                << SDL_GetError();
   }
   else
   {
      std::cout << "SDL is ready to go.\n";
   }

   return 0;
}