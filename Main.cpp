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
   SDL_Surface* surface = SDL_LoadBMP("./images/water.bmp");
   /**
   * Set the color key after loading the surface, and 
   *  before the texture. That is because when we create
   *  the texture, we're shipping the data over to the GPU.
   * The function below tells the computer to ignore those
   *  particular pixels and draw them as transparents. So if
   *  that haven't been already done in the image editor, we
   *  can use this function to make those pixels in the specified
   *  color transparent.
   */
   //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);
   /** 
   * Since we're done with the surface pointer, and the memory
   *  has been copied somewhere else, we can free that memory
   *  space.
   */
   SDL_FreeSurface(surface);

   // Horizontal Rectangles
   SDL_Rect rectangle;
   rectangle.x = 0;
   rectangle.y = 0;
   rectangle.w = 640;
   rectangle.h = 480;

   SDL_Rect rectangle2;
   rectangle2.x = -639;
   rectangle2.y = 0;
   rectangle2.w = 640;
   rectangle2.h = 480;
   
   // Vertical Rectangles
   SDL_Rect rectangle3;
   rectangle3.x = 0;
   rectangle3.y = 0;
   rectangle3.w = 640;
   rectangle3.h = 480;

   SDL_Rect rectangle4;
   rectangle4.x = 0;
   rectangle4.y = -480;
   rectangle4.w = 640;
   rectangle4.h = 480;

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
         if (event.type == SDL_MOUSEBUTTONDOWN)
         {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
               SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
            }
            else if (event.button.button == SDL_BUTTON_MIDDLE)
            {
               SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
               SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_MOD);
            }
         }
      }

      // (2) Handle Updates

      // (3) Clear and Draw the Screen
      // Set a color before clearing: set the background color
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(renderer);

      int w, h;
      // To query texture size if needed
      SDL_QueryTexture(texture, NULL, NULL, &w, &h);
      // Little hack here, to slow down simulation
      SDL_Delay(20);

      // Handle textures scrolling left and right
      rectangle.x++;
      if (rectangle.x > 639)
      {
         rectangle.x = -639;
      }
      rectangle2.x++;
      if (rectangle2.x > 639)
      {
         rectangle2.x = -639;
      }

      // Handle textures scrolling up and down
      rectangle3.y++;
      if (rectangle3.y > 479)
      {
         rectangle3.y = -480;
      }
      rectangle4.y++;
      if (rectangle4.y > 479)
      {
         rectangle4.y = -480;
      }

      // Order matters
      // Scrolling left and right (no blending)
      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
      SDL_RenderCopy(renderer, texture, NULL, &rectangle);
      SDL_RenderCopy(renderer, texture, NULL, &rectangle2);
      // Scrolling up and down (have trasnparency)
      SDL_RenderCopy(renderer, texture2, NULL, &rectangle3);
      SDL_RenderCopy(renderer, texture2, NULL, &rectangle4);

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