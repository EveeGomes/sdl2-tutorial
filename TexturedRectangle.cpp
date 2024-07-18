#include "TexturedRectangle.h"

TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, std::string filePath)
{
   SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
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