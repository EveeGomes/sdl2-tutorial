// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>

int main(int argc, char* argv[])
{
   /** 
   * Create window data type
   * This pointer will point to the window that is allocated
   *  from SDL_CreateWindow.
   */
   SDL_Window* window = nullptr;

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
   */
   window = SDL_CreateWindow("C++ SDL2 Window", 
                              20,
                              20,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);

   // Infinite loop for our application
   bool gameIsRunning = true;
   while (gameIsRunning)
   {
      SDL_Event event;
      // Start our event loop
      while (SDL_PollEvent(&event))
      {
         // Handle each specific event
         if (event.type == SDL_QUIT)
         {
            gameIsRunning = false;
         }
         if (event.type == SDL_MOUSEMOTION)
         {
            std::cout << "Mouse has been moved\n";
         }
         if (event.type == SDL_KEYDOWN)
         {
            std::cout << "A key has been pressed.\n";
            if (event.key.keysym.sym == SDLK_0)
            {
               std::cout << "0 was pressed!\n";
            }
            else
            {
               std::cout << "0 was not pressed.\n";
            }
         }
      }
   }

   /** 
   * We destroy our window. We are passing in the pointer that
   *  points to the memory allocated by the 'SDL_CreateWindow'
   *  function. Remember, this is a 'C-Style' API, we don't have
   *  destructors!
   */
   SDL_DestroyWindow(window);

   /** 
   * We safely uninitialize SDL2, that is, we are taking down the
   *  subsystems here before we exit our propgram.
   */
   SDL_Quit();

   return 0;
}