#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#else // This works for Mac

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#endif

// I recommend a map for filling in the resource manager

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>


class ResourceManager {
public:
    static ResourceManager& getInstance();

    void start(SDL_Renderer* renderer);
    void shutdown();

    SDL_Texture* loadSpriteTexture(const std::string& fileName); // TODO: another option is to pass renderer in parameter
    void unloadSpriteTexture(const std::string& fileName);

    TTF_Font* loadFont(const std::string& fileName, int fontSize);
    void unloadFont(const std::string& fileName);

    Mix_Music* loadMusic(const std::string fileName);
    void unloadMusic(const std::string fileName);


    Mix_Chunk* loadSound(std::string fileName);
    void unloadSound(std::string fileName);

    SDL_Texture* loadText(const std::string& define, const std::string& text, TTF_Font* font,
                          int size, SDL_Color color);


private:
    ResourceManager();
    ~ResourceManager();
    //static ResourceManager* _instance;
    ResourceManager(ResourceManager const&); // prevent from copying
    void operator=(ResourceManager const&);  // prevent from copying

    std::unordered_map<std::string, SDL_Texture*> m_texture;
    std::unordered_map<std::string, TTF_Font*> m_font;
    std::unordered_map<std::string, Mix_Music*> m_music;
    std::unordered_map<std::string, Mix_Chunk*> m_sound;
    std::unordered_map<std::string, SDL_Texture*> m_text;
    SDL_Renderer* m_renderer;





};




#endif //FINAL_RESOURCEMANAGER_H
