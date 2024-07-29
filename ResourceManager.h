#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

// C++ Standard Libraries
#include <string>
#include <unordered_map>

// Third-Party Library
#include <SDL.h>

class ResourceManager
{
private:
   /** 
   * Have the constructor in the private section so we won't be able to instantiate any of our resource managers!
   * Leave the destructor undefined as we're technically not going to destroy it anywhere.
   * Make sure that the copy constructor is also in this private section as we want to avoid copies of the resource manager.
   * Same for the copy assignment operator!
   */
   ResourceManager();
   ResourceManager(ResourceManager const&);
   ResourceManager operator=(ResourceManager const&);

   // keys: strings for the filepaths, values: pointers back to the SDL Surfaces that were allocated 
   std::unordered_map<std::string, SDL_Surface*> m_Surfaces;

public:
   /** 
   * Now in the public section we add what this class/type is able to do!
   * The actual task for this type is to retrieve some particular resource.
   */
   
   // Method to get an instance of RM that we're going to allocate and control
   static ResourceManager& GetInstance();

   /** 
   * Task to retrieve : SDL surface that has loaded in some bitmap.
   * i.e. we need our RM needs some key to return some value (in this case key: the string, value: the actual surface).
   *  For that we'll need a data structure: a hash table which in C++ the unordered map will do the trick!
   *  We'll make it a private member of this class.
   */
   SDL_Surface* GetSurface(std::string filepath);

};

#endif // !RESOURCE_MANAGER_H

