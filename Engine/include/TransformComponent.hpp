#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"
#include <SDL2/SDL.h>
#include <string>

class TransformComponent : public Component{
    public:

        TransformComponent(std::string); 
        ~TransformComponent();
        void Update() override;
        void Render(SDL_Renderer* renderer) override;
        void SetPosition(int x, int y);
        void SetLastPosition(int x, int y);
        // Getters
        float GetX();
        float GetY();
        int GetCaveId();

        int GetLastX();
        int GetLastY();
        std::string GetAnimType();

        // Setters
        void SetX(float newX);
        void SetY(float newY);
        void SetAnimType(std::string animName);

        void UnSetPosition(int caveId);
        void resetCaveId();
        std::string getTname();

        std::string getDetailsText();
        void setDetailsText(std::string text);
        bool ssScreen = true;
private:
        int m_caveId = 0;
        SDL_Point m_position;
        SDL_Point m_lastPosition;
        float m_roatation;
        float m_scale;
        std::string tname;
        std::string animName;
        std::string detailsTxt = "";


};


#endif
