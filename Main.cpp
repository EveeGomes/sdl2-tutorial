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
   * Grab the window surface
   */
   SDL_Surface* screen;

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
   window = SDL_CreateWindow("C++ SDL2 Window", 
                              20,
                              20,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);
   /** 
   * Get a pointer to the surface associated with the window.
   * This is used instead of creating a renderer, so we'll be
   *  drawing directly to the screen.
   */
   screen = SDL_GetWindowSurface(window);

   /** 
   * An image is another surface, so we create another surface
   *  for the image we want to load
   */
   SDL_Surface* image;
   image = SDL_LoadBMP("./images/digital-illustration-pascal-campion-7.bmp");
   SDL_BlitSurface(image, NULL, screen, NULL);
   SDL_FreeSurface(image);

   // Update the window surface (redraw our window surface)
   SDL_UpdateWindowSurface(window);

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
            /**
            * Handle the Keyboard state by retrieving the state of
            *  all of our scan codes that have been pressed, and
            *  checking which ones are 0 or 1.
            */
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_RIGHT])
            {
               std::cout << "Right arrow has been pressed.\n";
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