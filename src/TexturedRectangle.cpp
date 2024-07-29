// C++ Standard Libraries
#include <iostream>

#include "TexturedRectangle.h"
#include "ResourceManager.h"

TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, std::string filePath)
{
   /** 
   * Look up our surface
   * We can create this ResourceManager::GetInstance().GetSurface(filePath);
   *  as a pointer if we want some temporary pointer:
   */
   SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface("./images/digital-illustration-pascal-campion-7.bmp");

   /** 
   * The way our program is, we're getting to the disk 10 times in order to use the resource we have, the image
   *  and construct a TexturedRectangle. That's pretty expensive!
   * Adding a cout message we can see how many times this resource is used.
   */
   m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

   // 23:05 ep[26] We won't free it (we can add the functionality in our resource manager to free old surfaces or ones 
   //  that have been used for a while). That is something to consider now that we're managing the resources when do we
   //  give up ownership.
}

TexturedRectangle::~TexturedRectangle()
{
   /**
   * Destroy the texture to free memory since it won't be used
   *  anymore.
   */
   SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::SetRectangleProperties(int x, int y, int w, int h)
{
   m_rectangle.x = x;
   m_rectangle.y = y;
   m_rectangle.w = w;
   m_rectangle.h = h;
}

void TexturedRectangle::Update()
{
}

void TexturedRectangle::Render(SDL_Renderer*& renderer)
{
   // Drawing
   SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}