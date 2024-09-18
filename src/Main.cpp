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
#include "SDLApp.h"


// One possibility of creating as a global (that should be avoided, but for learning/teaching purpose we'll use for now)
SDLApp* app = nullptr;

// Also as globals...
// Capture mouse positions
int mouseX;
int mouseY;

void HandleEvents()
{
   //(1) Handle Input
   SDL_Event event;

   Uint32 buttons;
   buttons = SDL_GetMouseState(&mouseX, &mouseY);

   // Start our event loop
   while (SDL_PollEvent(&event))
   {
      // Handle each specific event
      if (event.type == SDL_QUIT)
      {
         //m_gameIsRunning = false;
      }
      //// Detect collision from our two shapes if mouse button is pressed
      //if (event.button.button == SDL_BUTTON_LEFT)
      //{
      //   // Since object2 is the one we're moving around, we'll work with it!
      //   if (object2.IsColliding(object1))
      //   {
      //      std::cout << "Is colliding\n";
      //   }
      //   else
      //   {
      //      std::cout << "Not colliding\n";
      //   }
      //}
   }
}

void HandleRendering()
{
   // Create two objects to render
   TexturedRectangle object1(app->GetRenderer(), "./images/digital-illustration-pascal-campion-7.bmp");
   TexturedRectangle object2(app->GetRenderer(), "./images/digital-illustration-pascal-campion-7.bmp");

   // (3) Clear and Draw the Screen
   // Set a color before clearing: set the background color
   SDL_SetRenderDrawColor(app->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
   // Gives us a clear "canvas"
   SDL_RenderClear(app->GetRenderer());

   // Do our drawing
   SDL_SetRenderDrawColor(app->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);

   // Set draw positions and sizes
   object1.Draw(50, 50, 100, 100);
   object2.Draw(mouseX, mouseY, 100, 100);

   // Render our objects
   object1.Render(app->GetRenderer());
   object2.Render(app->GetRenderer());

   // Finally show what we've drawn
   SDL_RenderPresent(app->GetRenderer());

   /**
   * This is how many milliseconds we want to slowdown the program
   */
   SDL_Delay(100);
}

int main(int argc, char* argv[])
{
   // Setup the SDLApp
   app = new SDLApp{ "New SDL2 Abstraction", 20, 20, 640, 480 };
   // Set the callback functions
   app->SetEventCallback(HandleEvents);
   app->SetRenderCallback(HandleRendering);
   // Run our application until terminated
   app->RunLoop();

   delete app;

   return 0;
}