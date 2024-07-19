// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Third-Party Library
#include <SDL.h>

// My classes
#include "TexturedRectangle.h" // API

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
   * So, in order to fix that, we have to manage the lifetime of those objects.
   * One way is to have a vector of TexturedRectangle pointers: vector<TexturedRectangle*>
   * However, as an API user perspective, it's better for memory management, to use
   *  shared pointers!
   */
   std::vector<std::shared_ptr<TexturedRectangle>> rects;
   for (int i = 0; i < 10; i++)
   {
      /** 
      * Now, everytime a rect is created, we have to manage its lifetime.
      * Create the shared pointers and push them to the vector
      */
      std::shared_ptr<TexturedRectangle> rect = 
         std::make_shared<TexturedRectangle>(renderer, "./images/digital-illustration-pascal-campion-7.bmp");
      rects.push_back(rect);
   }

   // Instantiate and initialize one time
   int row = 0;
   int col = 1;
   for (int i = 0; i < 10; i++)
   {
      rects[i]->SetRectangleProperties(100 * col, 30 * row, 200, 200);
      if (i % 3 == 0)
      {
         row++;
         col = 0;
      }
      col++;
   }

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
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(renderer);

      // Do our drawing
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      for (auto& rect : rects)
      {
         rect->Render(renderer);
      }

      // Finally show what we've drawn
      SDL_RenderPresent(renderer);
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