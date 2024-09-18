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
   

   // Setup a texture
   // Load up the pixels using a surface (CPU)
   SDL_Surface* surface = SDL_LoadBMP("./images/digital-illustration-pascal-campion-7.bmp");
   // Create a texture on the GPU using the surface so that we can later free the surface, ie free the pixels once we're done with them on the CPU.
   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);

   // Create a rectangle to draw
   SDL_Rect rectangle;
   rectangle.x = 50;
   rectangle.y = 100;
   rectangle.w = 160;
   rectangle.h = 160;

   // Draw a rectangle where the mouse is
   SDL_Rect rectMouse;
   rectMouse.x = 50;
   rectMouse.y = 100;
   rectMouse.w = 160;
   rectMouse.h = 160;

   // A rectangle to show where the previous rectangles intersect with each other, indicating there was a collision
   SDL_Rect rectIntersect;

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
      // Populate mouse coordinates
      int mouseX;
      int mouseY;
      Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
      rectMouse.x = mouseX;
      rectMouse.y = mouseY;

      // (2) Handle Updates

      // (3) Clear and Draw the Screen
      // Set a color before clearing: set the background color
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(renderer);

      // Do our drawing
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      // Draw rectangle
      SDL_RenderDrawRect(renderer, &rectangle);

      // Draw our rotated texture
      SDL_Point center;
      // This is the local rotation within the 'rectangle'. Rotation from the top-left corner
      //center.x = 0;
      //center.y = 0;
      
      // Rotation from the center of the rectangle
      center.x = rectangle.w / 2;
      center.y = rectangle.h / 2;
      static int angle = 0;
      angle++;
      
      SDL_RenderCopyEx(renderer, texture, nullptr, &rectangle, angle, &center, SDL_FLIP_NONE); // SDL2
      // in SDL3 use SDL_RenderTextureRotated() passing the same parameters! @https://wiki.libsdl.org/SDL3/SDL_RenderTextureRotated

      // Draw our rectangle at our mouse
      // (color it differently if we collide)
      if (SDL_IntersectRect(&rectangle, &rectMouse, &rectIntersect))
      {
         SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
         // Change rectangle color when intersect by the rectMouse
         SDL_RenderDrawRect(renderer, &rectIntersect);
         SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      }
      else
      {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      }
      SDL_RenderDrawRect(renderer, &rectMouse);

      // Finally show what we've drawn
      SDL_RenderPresent(renderer);

      /** 
      * This is how many milliseconds we want to slowdown the program
      */
      SDL_Delay(100);
   }



   /** 
   * We safely uninitialize SDL2, that is, we are taking down the
   *  subsystems here before we exit our propgram.
   */
   SDL_Quit();

   return 0;
}