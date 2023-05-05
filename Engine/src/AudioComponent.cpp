#include "../include/AudioComponent.hpp"

//AudioComponent::AudioComponent(TransformComponent* transformComponent) : m_transformcomponent(transformComponent){
//    // SDL_Init(SDL_INIT_AUDIO);
//    // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
//}
AudioComponent::AudioComponent() {
    // SDL_Init(SDL_INIT_AUDIO);
    // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

AudioComponent::~AudioComponent(){
    // Mix_FreeChunk(chunk);
    Mix_Quit();
}

void AudioComponent::Update() {

}

void AudioComponent::Render(SDL_Renderer* renderer) {}


void AudioComponent::loadSound(std::vector<std::string> filenames){
    for(auto &filename : filenames){
        Mix_Chunk *m = NULL;
        m = Mix_LoadWAV(("../Engine/assets/sounds/"+filename+".wav").c_str());
        sound_map.insert(std::make_pair(filename,m));
    }

	
}

void AudioComponent::playSound(std::string sound){
    // Find the element with key "banana"
    auto it = sound_map.find(sound);
    if (it != sound_map.end()) {
        if(sound == "monsterSound") {
            Mix_VolumeChunk(it->second, 34);
            Mix_PlayChannel(-1, it->second, 0);

        } else if(sound == "bgMusic") {
            Mix_PlayChannel(-2, it->second, 0);
        } else {
            Mix_PlayChannel(-1, it->second, 0);
        }

    }


   
}

void AudioComponent::initMixer(){
	SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    
}









// int AudioComponent::loadMusic(const char* filename){

//     // Mix_Music *m = NULL;
// 	// m = Mix_LoadMUS(filename);
// 	// if(m == NULL) {
// 	// 	printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
// 	// 	return -1;
// 	// }
// 	// music.push_back(m);
// 	// return music.size()-1;

// }

// int volume;
// void AudioComponent::setVolume(int v){
//     volume = (MIX_MAX_VOLUME * v) / 100;
// }

// int AudioComponent::playMusic(int m){
//     if(Mix_PlayingMusic() == 0) {
// 		Mix_Volume(1, volume);
// 		Mix_PlayMusic(music[m], -1);
// 	}
// 	return 0;
// }

// void AudioComponent::quitMixer(){
//     for(int s=0; s<sounds.size(); s++) {
// 		Mix_FreeChunk(sounds[s]);
// 		sounds[s]=NULL;
// 	}
// 	for(int s=0; s<music.size(); s++) {
// 		Mix_FreeMusic(music[s]);
// 		music[s]=NULL;
// 	}
// 	Mix_Quit();
// }

// void AudioComponent::togglePlay(){
//     if(Mix_PausedMusic() == 1) {
// 		Mix_ResumeMusic();
// 	} else {
// 		Mix_PauseMusic();
// 	}
// }