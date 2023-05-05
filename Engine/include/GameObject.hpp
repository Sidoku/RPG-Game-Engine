#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Component.hpp"
#include <vector>
#include <SDL2/SDL.h>


class Component;
class GameObject{
    public:
        GameObject();
        ~GameObject();

    // Note: You may want to add member functions like 'Update' or 'Render'
    // Note: You may want to add member functions like "AddComponent" or "RemoveComponent"
    void AddComponent(Component* component);
    void Update();
    void Render(SDL_Renderer* renderer);
    private:
        std::vector<Component*> m_components;
};


#endif
