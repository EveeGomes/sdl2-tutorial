// C++ Standard Libraries
#include <iostream>

#include "TexturedRectangle.h"

TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, std::string filePath)
{
   SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
   /** 
   * The way our program is, we're getting to the disk 10 times in order to use the resource we have, the image
   *  and construct a TexturedRectangle. That's pretty expensive!
   * Adding a cout message we can see how many times this resource is used.
   */
   std::cout << "Image loaded: " << filePath.c_str() << std::endl;
   m_texture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);
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