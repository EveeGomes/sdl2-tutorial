// C++ Standard Libraries
#include <iostream>

// Third-Party Library
#include <SDL.h>
// Include GLAD
#include <glad/glad.h>

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
   * Before we create our window, specify OpenGL version
   */
   // Version 4.1
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
   // Core profile
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                       SDL_GL_CONTEXT_PROFILE_CORE);
   // Update the window quite often between front and back buffers
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   // Make sure it has 24 bits for the color
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   
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
                              SDL_WINDOW_SHOWN | 
                              SDL_WINDOW_OPENGL);

   /** 
   * OpenGL setup the graphics context
   * Create the OpenGL context object. Then, use CreateContext()
   *  to create an OpenGL context associated with the window we
   *  have.
   */
   SDL_GLContext context;
   context = SDL_GL_CreateContext(window);

   /** 
   * Setup our function pointers.
   * This is important so it knows where to find the functions.
   */
   gladLoadGLLoader(SDL_GL_GetProcAddress);

   // Infinite loop for our application
   bool gameIsRunning = true;
   while (gameIsRunning)
   {
      // Size of OpenGL viewport:
      glViewport(20, 20, 640, 480);

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
            std::cout << "A key has been pressed.\n";
            if (event.key.keysym.sym == SDLK_0)
            {
               std::cout << "0 was pressed!\n";
            }
            else
            {
               std::cout << "0 was not pressed.\n";
            }
         }
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

         /** 
         * To test OpenGL:
         * Clear the window every frame to give us a new color
         *  of our screen
         */
         glClearColor(1.f, 0.f, 0.f, 1.f); // red
         glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

         /** 
         * Let SDL know that we're having double buffer (front
         *  and back) and it keeps refreshing and flipping between
         *  them.
         */
         SDL_GL_SwapWindow(window);
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