// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Third-Party Library
#include <SDL.h>

// My classes
#include "TexturedRectangle.h" // API
#include "AnimatedSprite.h"

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

   ///** 
   //* So, in order to fix that, we have to manage the lifetime of those objects.
   //* One way is to have a vector of TexturedRectangle pointers: vector<TexturedRectangle*>
   //* However, as an API user perspective, it's better for memory management, to use
   //*  shared pointers!
   //*/
   //std::vector<std::shared_ptr<TexturedRectangle>> rects;
   //for (int i = 0; i < 10; i++)
   //{
   //   /** 
   //   * Now, everytime a rect is created, we have to manage its lifetime.
   //   * Create the shared pointers and push them to the vector
   //   */
   //   std::shared_ptr<TexturedRectangle> rect = 
   //      std::make_shared<TexturedRectangle>(renderer, "./images/digital-illustration-pascal-campion-7.bmp");
   //   rects.push_back(rect);
   //}

   //// Instantiate and initialize one time
   //int row = 0;
   //int col = 1;
   //for (int i = 0; i < 10; i++)
   //{
   //   rects[i]->SetRectangleProperties(100 * col, 30 * row, 200, 200);
   //   if (i % 3 == 0)
   //   {
   //      row++;
   //      col = 0;
   //   }
   //   col++;
   //}

   /** 
   *  x = 100, y = 0 i = 0
      0 % 3 == 0
      row = 1
      col = 0
      col++ = 1

      x = 100, y = 30 i = 1
      x = 200, y = 30 i = 2
      x = 300, y = 30 i = 3
      3 % 3 == 0
      row = 2
      col = 0
      col++ = 1

      x = 100, y = 60 i = 4
      x = 200, y = 60 i = 5
      x = 300, y = 60 i = 6 
      3 % 3 == 0
      row = 3
      col = 0
      col++ = 1

      x = 100, y = 90 i = 7
      x = 200, y = 90 i = 8
      x = 300, y = 90 i = 9
   */

   /** 
   * Using AnimatedSprite type
   */
   AnimatedSprite animatedSprite(renderer, "./images/Character_Down_grid2.bmp");
   animatedSprite.Draw(200, 200, 150, 150);

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

      //for (auto& rect : rects)
      //{
      //   rect->Render(renderer);
      //}

      // Have a counter to choose which frame to work
      static int frameNumber = 0;

      animatedSprite.PlayFrame(0, 0, 32, 32, frameNumber);
      animatedSprite.Render(renderer);
      frameNumber++;
      if (frameNumber > 4)
      {
         frameNumber = 0;
      }

      // Finally show what we've drawn
      SDL_RenderPresent(renderer);

      /** 
      * This is how many milliseconds we want to slowdown the program
      */
      SDL_Delay(60);
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