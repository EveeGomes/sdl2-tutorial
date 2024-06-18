// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>

/** 
* Helper function to set a pixel color.
* Abstract the update that we were doing inside the loop 
* @params x,y: pixels coordinates.
* @params colors: use uint8_t for the colors because they range 
*  between 0 - 255, so there's no need to be too large data type!
* @param surface: to not worry about locking the surface all the
*  time.
*/
void SetPixel(SDL_Surface* surface, 
              int x, int y, 
              uint8_t red, uint8_t green, uint8_t blue)
{
   /**
   * Once locked, surface->pixels is safe to access.
   * With it locked, we can modify it.
   */
   SDL_LockSurface(surface);
   SDL_memset(surface->pixels,
              255,
              surface->h * surface->pitch);
   std::cout << "Left mouse button was pressed at "
             << "x,y position ("
             << x << "," << y << ")\n";
   /** 
   * The pointer to a pixel is of type void* so we need to cast
   *  it! If not NULL, it contains the raw pixel data for the
   *  surface.
   * In [Ep.15] @13:39, Mike shows that pitch corresponds to the
   *  length of a single row of pixels in the window (how many
   *  bytes are in a row): w * 3 = pitch
   *  [r|g|b|r|g|b|...]
   */
   uint8_t* pixelArray = (uint8_t*)surface->pixels;
   pixelArray[y * surface->format->BytesPerPixel + x] = red;

   SDL_UnlockSurface(surface);
}

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
   //SDL_Surface* image;
   //image = SDL_LoadBMP("./images/digital-illustration-pascal-campion-7.bmp");
   //SDL_BlitSurface(image, NULL, screen, NULL);
   //SDL_FreeSurface(image);

   // Update the window surface (redraw our window surface)
   SDL_UpdateWindowSurface(window);

   // Infinite loop for our application
   bool gameIsRunning = true;
   while (gameIsRunning)
   {
      SDL_Event event;
      
      // Mouse State
      int x, y;
      Uint32 buttons;
      buttons = SDL_GetMouseState(&x, &y);

      // Start our event loop
      while (SDL_PollEvent(&event))
      {
         // Handle each specific event
         if (event.type == SDL_QUIT)
         {
            gameIsRunning = false;
         }
         if (event.button.button == SDL_BUTTON_LEFT)
         {
            /** 
            * After the changes, update the surface.
            * It's a strategy of "flipping" the buffer. So we make
            *  modifications to the color, and once they're done 
            *  to whatever surface we've been drawing to, we flip
            *  to the newly updated surface and then it can make 
            *  modifications in the background. That's the double
            *  buffering strategy.
            */
            SDL_UpdateWindowSurface(window);
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