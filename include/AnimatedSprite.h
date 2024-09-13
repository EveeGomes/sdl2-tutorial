#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

// C++ Standard Libraries
#include <string>

// Third Party Library
#include <SDL.h>

/** 
* Usually when implementing something, it's nice to think about what the interface is itself. 
*  Then, we can think about some of the implementation details! -Mike Shah.
*/

class AnimatedSprite
{
private:
   // Where we're selecting from
   SDL_Rect m_src{};
   // Where we're rendering
   SDL_Rect m_dst{};
   SDL_Texture* m_texture = nullptr;

public:
   // Constructor
   AnimatedSprite(SDL_Renderer*& renderer, std::string filepath);

   // Destructor
   ~AnimatedSprite();

   // Tell the x,y position and size of the rectangle we're drawing
   void Draw(int posX, int posY, int w, int h);

   // Select from the spritesheet and play a specific frame
   void PlayFrame(int x, int y, int w, int h, int frame);

   // Update every frame
   void Update();

   // Render
   void Render(SDL_Renderer*& renderer);
};


#endif // !ANIMATED_SPRITE_H