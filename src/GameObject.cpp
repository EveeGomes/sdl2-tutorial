#include "GameObject.h"

GameEntity::GameEntity()
{
   m_sprite = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritePath)
{
   m_renderer = renderer;
   m_sprite = new TexturedRectangle{ m_renderer, spritePath };
}

GameEntity::~GameEntity()
{
}

void GameEntity::Update()
{
}

void GameEntity::Render()
{
   // Checking if our sprite isn't null in a reverse order which is a bit safer
   if (nullptr == m_sprite)
   {
      m_sprite->Render(m_renderer);
   }
}
