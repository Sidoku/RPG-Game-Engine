#ifndef AUDIOCOMPONENT_HPP
#define AUDIOCOMPONENT_HPP

#include "Component.hpp"

#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>
#include "TransformComponent.hpp"
#include <unordered_map>

class AudioComponent : public Component{

    public:
      
        AudioComponent();
       // AudioComponent(TransformComponent* transformComponent);
        ~AudioComponent();
        
        // int loadMusic(const char* filename) {}
        void Update() override;
        void Render(SDL_Renderer* renderer) override;

        void initMixer();
        void loadSound(std::vector<std::string> filenames);
        void playSound(std::string sound);

        // void setVolume(int v);

        // int playMusic(int m) {}

        // void quitMixer();

        // void togglePlay();
        

    private: 
        // std::vector<Mix_Chunk*> sounds;
        // std::vector<Mix_Music*> music;
        std::unordered_map<std::string, Mix_Chunk*> sound_map;
        TransformComponent* m_transformcomponent;
};

#endif