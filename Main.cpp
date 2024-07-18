// C++ Standard Libraries
#include <iostream>
#include <string>

// Third-Party Library
#include <SDL.h>

class TexturedRectangle
{
private:
   SDL_Rect m_rectangle;
   SDL_Texture* m_texture;

public:
   /** 
   * Responsible for setting up our rectangle and its properties!
   * Have a constructor that can handle the image we want to create
   *  and then immediately create a texture surface from that.
   * We'll get the renderer as a reference and have the texture as a member variable.
   *  This is a decision that might change later as to make the user of our API more
   *  comfortable instead of keeping passing the renderer over the methods. In other hands
   *  it's a good thing to keep everything in the same renderer.
   */
   TexturedRectangle(SDL_Renderer*& renderer, std::string filePath) // renderer is being passed as a pointer reference!
   {
      SDL_Surface* surface = SDL_LoadBMP(filePath.c_str()); // use c_str() because SDL is a C-based API!!!
      m_texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);

      // Create a rectangle
      
   }
   
   ~TexturedRectangle()
   {
      /**
      * Destroy the texture to free memory since it won't be used
      *  anymore.
      */
      SDL_DestroyTexture(m_texture);
   }

   // Rule of 3: good practice!
   // Copy constructor
   // Copy assignment operator

   /** 
   * Have setters in order to set the values of the SDL_Rect, we now have as a member variable
   */
   void SetRectangleProperties(int x, int y, int w, int h)
   {
      m_rectangle.x = x;
      m_rectangle.y = y;
      m_rectangle.w = w;
      m_rectangle.h = h;
   }

   void Update()
   {

   }

   void Render(SDL_Renderer*& renderer) // pointer reference
   {
      // Drawing
      SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
   }
};

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