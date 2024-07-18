// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

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

   /** 
   * Initialize the Image library and check if it was successful.
   */
   int flags = IMG_INIT_PNG;
   int initStatus = IMG_Init(flags);
   if ((initStatus & flags) != flags)
   {
      std::cout << "SDL2_Image format not available.\n";
   }

   // Create a surface (that is gonna hold our pixels)
   SDL_Surface* image;
   // Load up something into the surface
   image = IMG_Load("./images/digital-illustration-pascal-campion-7.png");
   if (!image)
   {
      std::cout << "Image not loaded..." << std::endl;
   }

   /** 
   * Render the image to a rectangle. But for that we first need
   *  a texture.
   */
   SDL_Texture* ourPNG = SDL_CreateTextureFromSurface(renderer, image);

   // Infinite loop for our application
   bool gameIsRunning = true;
   while (gameIsRunning)
   {
      //(1) Handle Input
      SDL_Event event;
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
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(renderer);

      // Finally show what we've drawn
      SDL_RenderPresent(renderer);
   }
   /** 
   * Destroy the texture to free memory since it won't be used
   *  anymore.
   */
   //SDL_DestroyTexture(texture);

   /** 
   * We destroy our window. We are passing in the pointer that
   *  points to the memory allocated by the 'SDL_CreateWindow'
   *  function. Remember, this is a 'C-Style' API, we don't have
   *  destructors!
   */
   SDL_DestroyWindow(window);

   // Free our png image surface
   SDL_FreeSurface(image);
   // Detroy our texture
   SDL_DestroyTexture(ourPNG);

   // Unload the dynamically loaded image libraries
   IMG_Quit();

   /** 
   * We safely uninitialize SDL2, that is, we are taking down the
   *  subsystems here before we exit our propgram.
   */
   SDL_Quit();

   return 0;
}