// C++ Standard Libraries
#include <iostream>

#include "TexturedRectangle.h"
#include "ResourceManager.h"

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filePath)
{
   /** 
   * Look up our surface
   * We can create this ResourceManager::GetInstance().GetSurface(filePath);
   *  as a pointer if we want some temporary pointer:
   */
   SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filePath);

   /** 
   * The way our program is, we're getting to the disk 10 times in order to use the resource we have, the image
   *  and construct a TexturedRectangle. That's pretty expensive!
   * Adding a cout message we can see how many times this resource is used.
   */
   m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

   // 23:05 ep[26] We won't free it (we can add the functionality in our resource manager to free old surfaces or ones 
   //  that have been used for a while). That is something to consider now that we're managing the resources when do we
   //  give up ownership.

   // Set default positions
   m_rectangle.x = 0;
   m_rectangle.y = 0;
   m_rectangle.w = 32;
   m_rectangle.h = 32;

}

TexturedRectangle::~TexturedRectangle()
{
   /**
   * Destroy the texture to free memory since it won't be used
   *  anymore.
   */
   SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::Draw(int x, int y, int w, int h)
{
   m_rectangle.x = x;
   m_rectangle.y = y;
   m_rectangle.w = w;
   m_rectangle.h = h;
}

SDL_bool TexturedRectangle::IsColliding(const TexturedRectangle& obj)
{
   /** 
   * Use an SDL function that checks if two SDL_Rect has intersections.
   * We need to extract an SDL_Rect from a TexturedRectangle. This type already has an
   *  SDL_Rect as a member: m_rectangle, so we'll write a getter to use it here!
   */
   return SDL_HasIntersection(&m_rectangle, obj.GetRectangle());
}

void TexturedRectangle::Update()
{
}

void TexturedRectangle::Render(SDL_Renderer* renderer)
{
   // Drawing
   SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}