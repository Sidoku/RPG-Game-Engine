#ifndef CONTROLLERCOMPONENT_HPP 
#define CONTROLLERCOMPONENT_HPP

#include <SDL2/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "GameWorld/GameModel.h"
#include "AudioComponent.hpp"


class ControllerComponent : public Component{
    public:
        ControllerComponent(TransformComponent* transformComponent1, TransformComponent* transformComponent2,
                            TransformComponent* transformComponent3,TransformComponent* transformComponent4,
                            TransformComponent* transformComponent5, TransformComponent* transformComponent6,
                            TransformComponent* transformComponent7,
                            AudioComponent* audioComponent, GameModel* model);
                         
        ~ControllerComponent();
        void Update() override;
        SDL_Point m_lastPosition;


    private:
        GameModel* model;
        TransformComponent* m_transformComponent;
        TransformComponent* t_transformComponent;
        TransformComponent* a_transformComponent;
        TransformComponent* p_transformComponent;
        TransformComponent* d_transformComponent;
        TransformComponent* ss_transformComponent;
        AudioComponent* audioComponent;
        TransformComponent* txt_transformComponent;
        float m_moveSpeed = 1;
        bool shootArrow = false;
        bool shootDirection = false;
        bool diceRoll = false;
        bool ismove = false;

};


#endif
