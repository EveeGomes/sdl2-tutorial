// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>
#include <SDL_ttf.h>

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
   * Just like when we initialize our graphics subsystem,
   *  we need to do the same for our font system.
   */
   if (TTF_Init() == -1)
   {
      std::cout << "Could not initialize SDL2 ttf, error: "
                << TTF_GetError()
                << std::endl;
   }
   else
   {
      std::cout << "SDL2_ttf is ready to go!\n";
   }

   /** 
   * Load the font file and set the font size.
   * Make error handling by checking if the font has loaded,
   *  if it hasn't (the pointer is nullptr) show a message
   *  error and terminate the program.
   */
   TTF_Font* ourFont = TTF_OpenFont("./fonts/PressStart2P-Regular.ttf", 32);
   if (ourFont == nullptr)
   {
      std::cout << "Could not load font.\n";
      exit(1);
   }
   
   /** 
   * As ttfs are a pixel base format, we're going to send the
   *  pixels data to the surface.
   */
   // Pixel from our text
   SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont, "Mike SDL2 Tutorial Series", { 255, 255, 255 });
   // Take a surface and create a texture from it (Setup the texture):
   SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
   // Then, release the surface as the pixels data are on the texture
   SDL_FreeSurface(surfaceText);

   SDL_Rect rectangle;
   rectangle.x = 10;
   rectangle.y = 10;
   rectangle.w = 400;
   rectangle.h = 100;

   ///** 
   //* Create a surface to load an image.
   //* A surface in SDL is a way to load pixel data onto an internal
   //*  image format. Then, that pixel data can be taken and rendered
   //*  to a texture in order to be faster.
   //* So, rendering a text onto a texture, makes it way faster.
   //* If a change is needed, surfaces have to be recreated so it's
   //*  better to think about how to optimize it. (Ep. 22 5:20)
   //*/
   //// Create a surface to load an image
   //SDL_Surface* surface = SDL_LoadBMP("./images/water.bmp");
   ///**
   //* Set the color key after loading the surface, and 
   //*  before the texture. That is because when we create
   //*  the texture, we're shipping the data over to the GPU.
   //* The function below tells the computer to ignore those
   //*  particular pixels and draw them as transparents. So if
   //*  that haven't been already done in the image editor, we
   //*  can use this function to make those pixels in the specified
   //*  color transparent.
   //*/
   ////SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

   //SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   //SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);
   ///** 
   //* Since we're done with the surface pointer, and the memory
   //*  has been copied somewhere else, we can free that memory
   //*  space.
   //*/
   //SDL_FreeSurface(surface);

   // Horizontal Rectangles
   //SDL_Rect rectangle;
   //rectangle.x = 0;
   //rectangle.y = 0;
   //rectangle.w = 640;
   //rectangle.h = 480;

   //SDL_Rect rectangle2;
   //rectangle2.x = -639;
   //rectangle2.y = 0;
   //rectangle2.w = 640;
   //rectangle2.h = 480;
   //
   //// Vertical Rectangles
   //SDL_Rect rectangle3;
   //rectangle3.x = 0;
   //rectangle3.y = 0;
   //rectangle3.w = 640;
   //rectangle3.h = 480;

   //SDL_Rect rectangle4;
   //rectangle4.x = 0;
   //rectangle4.y = -480;
   //rectangle4.w = 640;
   //rectangle4.h = 480;

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
         //if (event.type == SDL_MOUSEBUTTONDOWN)
         //{
         //   if (event.button.button == SDL_BUTTON_LEFT)
         //   {
         //      SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
         //   }
         //   else if (event.button.button == SDL_BUTTON_MIDDLE)
         //   {
         //      SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
         //   }
         //   else if (event.button.button == SDL_BUTTON_RIGHT)
         //   {
         //      SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_MOD);
         //   }
         //}
      }

      // (2) Handle Updates

      // (3) Clear and Draw the Screen
      // Set a color before clearing: set the background color
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
      // Gives us a clear "canvas"
      SDL_RenderClear(renderer);

      SDL_RenderCopy(renderer, textureText, NULL, &rectangle);

      //int w, h;
      //// To query texture size if needed
      //SDL_QueryTexture(texture, NULL, NULL, &w, &h);
      //// Little hack here, to slow down simulation
      //SDL_Delay(20);

      //// Handle textures scrolling left and right
      //rectangle.x++;
      //if (rectangle.x > 639)
      //{
      //   rectangle.x = -639;
      //}
      //rectangle2.x++;
      //if (rectangle2.x > 639)
      //{
      //   rectangle2.x = -639;
      //}

      //// Handle textures scrolling up and down
      //rectangle3.y++;
      //if (rectangle3.y > 479)
      //{
      //   rectangle3.y = -480;
      //}
      //rectangle4.y++;
      //if (rectangle4.y > 479)
      //{
      //   rectangle4.y = -480;
      //}

      // Order matters
      // Scrolling left and right (no blending)
      //SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
      //SDL_RenderCopy(renderer, texture, NULL, &rectangle);
      //SDL_RenderCopy(renderer, texture, NULL, &rectangle2);
      //// Scrolling up and down (have trasnparency)
      //SDL_RenderCopy(renderer, texture2, NULL, &rectangle3);
      //SDL_RenderCopy(renderer, texture2, NULL, &rectangle4);

      // Finally show what we've drawn
      SDL_RenderPresent(renderer);
   }
   /** 
   * Destroy the texture to free memory since it won't be used
   *  anymore.
   */
   //SDL_DestroyTexture(texture);
   SDL_DestroyTexture(textureText);

   /** 
   * We destroy our window. We are passing in the pointer that
   *  points to the memory allocated by the 'SDL_CreateWindow'
   *  function. Remember, this is a 'C-Style' API, we don't have
   *  destructors!
   */
   SDL_DestroyWindow(window);

   // Close our font subsystem
   TTF_CloseFont(ourFont);

   /** 
   * We safely uninitialize SDL2, that is, we are taking down the
   *  subsystems here before we exit our propgram.
   */
   SDL_Quit();

   return 0;
}