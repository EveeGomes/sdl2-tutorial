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
   * Add the SDL_WINDOW_OPENGL flag so it can be a window
   *  usable with an OpenGL context.
   */
   window = SDL_CreateWindow("C++ SDL2 Window", 
                              20,
                              20,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);

   SDL_Renderer* renderer = nullptr;
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   
   // Create a surface to load an image
   SDL_Surface* surface = SDL_LoadBMP("./images/kong1.bmp");
   SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   /** 
   * Since we're done with the surface pointer, and the memory
   *  has been copied somewhere else, we can free that memory
   *  space.
   */
   SDL_FreeSurface(surface);


   // Create a rectangle
   SDL_Rect rectangle;
   rectangle.x = 50;
   rectangle.y = 100;
   rectangle.w = 300;
   rectangle.h = 300;

   // Infinite loop for our application
   bool gameIsRunning = true;
   while (gameIsRunning)
   {
      SDL_Event event;
      //(1) Handle Input
      // Start our event loop
      while (SDL_PollEvent(&event))
      {
         // Handle each specific event
         if (event.type == SDL_QUIT)
         {
            gameIsRunning = false;
         }
      }
      // (2) Handle Updates

      // (3) Clear and Draw the Screen
      // Set a color before clearing: set the background color
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(renderer);

      // Do our drawing
      // Specify what color to draw the line
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(renderer, 5, 5, 100, 120);

      //SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawRect(renderer, &rectangle);
      SDL_RenderCopy(renderer, texture, NULL, &rectangle);

      // Finally show what we've drawn
      SDL_RenderPresent(renderer);
   }
   /** 
   * Destroy the texture to free memory since it won't be used
   *  anymore.
   */
   SDL_DestroyTexture(texture);

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