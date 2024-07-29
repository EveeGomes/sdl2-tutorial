#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::ResourceManager(ResourceManager const&)
{

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs)
{

}

ResourceManager& ResourceManager::GetInstance()
{
   /** 
   * Statically allocate one pointer to a ResourceManager
   * We use static as for C++ 11 this is thread safe and guaranteed to be only instantiated once
   *  even if we have multiple threads working with this particular function.
   */
   static ResourceManager* s_Instance = new ResourceManager;

   /** 
   * Returning pointers (like the actual pointer: return s_Instance;) is dangerous because then the user
   * could delete this particular instance and we'd have to add a bunch of error checking code.
   * So, to avoid that we return a reference to a ResourceManager! And to do that we dereference our
   *  static instance: s_Instance.
   */
   return *s_Instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath)
{
   return nullptr;
}

