#include "AnimatedSprite.h"
#include "ResourceManager.h"

AnimatedSprite::AnimatedSprite(SDL_Renderer*& renderer, std::string filepath)
{
   SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);
   m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
}

AnimatedSprite::~AnimatedSprite()
{
   SDL_DestroyTexture(m_texture);
}

void AnimatedSprite::Draw(int posX, int posY, int w, int h)
{
   // Create a rectangle
   m_dst.x = posX;
   m_dst.y = posY;
   m_dst.w = w;
   m_dst.h = h;

}

void AnimatedSprite::PlayFrame(int x, int y, int w, int h, int frame)
{
   // w * frame so it traverse and reach the next frame, ie that's the offset 
   m_src.x = x + w * frame;
   m_src.y = y;
   m_src.w = w;
   m_src.h = h;
}

void AnimatedSprite::Update()
{
}

void AnimatedSprite::Render(SDL_Renderer*& renderer)
{
   /** 
   * Select from a specif texture, which is the spritesheet.
   */
   // check m_texture is valid before using it? if(m_texture)...
   SDL_RenderCopy(renderer, m_texture, &m_src, &m_dst);
}
