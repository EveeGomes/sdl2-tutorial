#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H

// C++ Standard Libraries
#include <string>

// Third-Party Library
#include <SDL.h>

class TexturedRectangle
{
private:
   SDL_Rect m_rectangle;
   /**
   * One improvement we can think of is to use smart pointers to avoid memory leaks.
   * However, since we're dealing with a C-based library, leaving as it is also seems as a good decision.
   */
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
   TexturedRectangle(SDL_Renderer*& renderer, std::string filePath);

   ~TexturedRectangle();

   // Rule of 3: good practice!
   // Copy constructor
   // Copy assignment operator
   // Or even rule of 5 with move and move assignment, depending on our API

   /**
   * Have setters in order to set the values of the SDL_Rect, we now have as a member variable
   */
   void SetRectangleProperties(int x, int y, int w, int h);

   // Update every frame
   void Update();

   void Render(SDL_Renderer*& renderer);
};

#endif // !TEXTUREDRECTANGLE_H