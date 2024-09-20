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
#include "GameEntity.h"


// One possibility of creating as a global (that should be avoided, but for learning/teaching purpose we'll use for now)
SDLApp* app = nullptr;

// Make them global for now...
// Eventually, we will want some sort of factory (or some other way) to manage object creation in our app.
// Create two objects to render
GameEntity* object1;
GameEntity* object2;

void HandleEvents()
{
   //(1) Handle Input
   SDL_Event event;

   // Start our event loop
   while (SDL_PollEvent(&event))
   {
      // Handle each specific event
      if (event.type == SDL_QUIT)
      {
         app->StopAppLoop();
      }
      // Detect collision from our two shapes if mouse button is pressed
      if (event.button.button == SDL_BUTTON_LEFT)
      {
         //// Since object2 is the one we're moving around, we'll work with it!
         //if (object2->IsColliding(*object1))
         //{
         //   std::cout << "Is colliding\n";
         //}
         //else
         //{
         //   std::cout << "Not colliding\n";
         //}
      }
   }
}

void HandleRendering()
{
   // Set draw positions and sizes
   //object1->Draw(50, 50, 100, 100);
   //object2->Draw(app->GetMouseX(), app->GetMouseY(), 100, 100);

   // Render our objects
   object1->Render();
   object2->Render();
}

int main(int argc, char* argv[])
{
   // Setup the SDLApp
   app = new SDLApp{ "New SDL2 Abstraction", 20, 20, 640, 480 };

   // Create any objects in our scene
   object1 = new GameEntity{ app->GetRenderer(), "./images/digital-illustration-pascal-campion-7.bmp" };
   object2 = new GameEntity{ app->GetRenderer(), "./images/digital-illustration-pascal-campion-7.bmp" };

   // Set the callback functions
   app->SetEventCallback(HandleEvents);
   app->SetRenderCallback(HandleRendering);
   // Run our application until terminated
   app->RunLoop();

   // Clean up our application
   delete app;
   delete object1;
   delete object2;

   return 0;
}