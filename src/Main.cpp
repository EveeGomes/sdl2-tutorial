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

int main(int argc, char* argv[])
{
   // Create an instance of SDLApp so everything that happens in our program, happens through an instance of SDLApp.
   SDLApp app{ "New SDL2 Abstraction", 20, 20, 640, 480 };
   app.RunLoop();

   // Create two objects to render
   TexturedRectangle object1(renderer, "./images/digital-illustration-pascal-campion-7.bmp");
   TexturedRectangle object2(renderer, "./images/digital-illustration-pascal-campion-7.bmp");

   /** 
   * We safely uninitialize SDL2, that is, we are taking down the
   *  subsystems here before we exit our propgram.
   */
   SDL_Quit();

   return 0;
}