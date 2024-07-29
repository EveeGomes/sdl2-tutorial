#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::ResourceManager(ResourceManager const&)
{

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs)
{
   // TODO: Although we do not need this for a singleton
   return *this; // just so it compiles
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
   /** 
   * The idea here is to look through our map (m_Surfaces) and see if any surface exists.
   * ie, we'll see if a file exists, and if the file does exist, then return the associated surface.
   * "That's because any time we load something, we're going to always, in this particular function GetSurface,
   *  allocate an SDL_Surface."
   * So, if the file exists, we'll grab the surface, if it doesn't we'll load the file.
   */
   // Create an iterator and assign it to the value returned in case we find the key in the map
   auto Search = m_Surfaces.find(filepath);
   // If we haven't reached the end, then we've found the surface
   if (Search != m_Surfaces.end())
   {
      // Return the surface with that key
      return m_Surfaces[filepath];
   }
   // else, we allocate that surface
   else
   {
      SDL_Surface* Surface = SDL_LoadBMP(filepath.c_str());
      // then we add it to our map
      m_Surfaces.insert(std::make_pair(filepath, Surface));
   }

   // Since not all cases it returns a valid pointer.
   return nullptr;
}

