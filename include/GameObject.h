#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "TexturedRectangle.h"

// C++ Standard Libraries
#include <string>

// Third-Party Library
#include "SDL.h"

// Same as Game Entity
class GameEntity
{
public:
   // Constructors
   GameEntity();
   GameEntity(SDL_Renderer* renderer, std::string spritePath);
   // Destructor
   ~GameEntity();

   void Update();
   void Render();

private:
   // Every GameEntity should have its own TexturedRectangle
   // Make it a pointer because not every GameEntity needs a TexturedRectangle. So the ones that needs it, just initalize it and use it.
   // We could handle this as a function that initializes it or something that is passed to GameEntity. For now we'll initialize it in the
   //  constructor to null.
   TexturedRectangle* m_sprite;

   // Store the renderer passed in the constructor for in case we need it later
   SDL_Renderer* m_renderer;
};

#endif