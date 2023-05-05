#ifndef TCONTROLLERCOMPONENT_HPP
#define TCONTROLLERCOMPONENT_HPP

#include <SDL2/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "GameWorld/GameModel.h"



class TreasureControllerComponent : public Component{
    public:
        TreasureControllerComponent(TransformComponent* transformComponent, GameModel* model);
        ~TreasureControllerComponent();
        void Update() override;
        SDL_Point m_lastPosition;


    private:
        GameModel* model;
        TransformComponent* m_transformComponent;
        float m_moveSpeed = 1;

};


#endif
