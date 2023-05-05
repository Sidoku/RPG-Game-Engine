#ifndef COMPONENT_HPP 
#define COMPONENT_HPP

#include <SDL2/SDL.h>


class Component{
    public:
        Component();
        ~Component() {};
        virtual void Update();
        virtual void Render(SDL_Renderer* renderer);

};


#endif
