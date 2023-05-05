#include <sstream>
#include "../include/ResourceManager.hpp"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}



ResourceManager& ResourceManager::getInstance() {
    static ResourceManager _instance;
    return _instance;
}

SDL_Texture* ResourceManager::loadSpriteTexture(const std::string& fileName) {
    if (m_texture.find(fileName) == m_texture.end()) {
        SDL_Surface* surface = SDL_LoadBMP(fileName.c_str());
        if (surface == nullptr) {
            std::cout << "Error: " << SDL_GetError() << std::endl;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
        m_texture[fileName] = texture;
    }
    return m_texture[fileName];
}

void ResourceManager::unloadSpriteTexture(const std::string& fileName) {
    if (m_texture.find(fileName) != m_texture.end()) {
        SDL_DestroyTexture(m_texture[fileName]);
        m_texture.erase(fileName);
    }else{
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}

TTF_Font* ResourceManager::loadFont(const std::string& fileName, int fontSize) {
    std::stringstream ss;
    ss << fileName << fontSize; // formatting file name (example filename: "Times", fontsize: 20 -> Times20)
    std::string fontName = ss.str();
    if (m_font.find(fontName) == m_font.end()) {
        TTF_Font* font = TTF_OpenFont(fileName.c_str(), fontSize);
        if (font == nullptr) {
            std::cout << "Error: " << SDL_GetError() << std::endl;
        }
        m_font[fontName] = font;
    }
    return m_font[fontName];
}

void ResourceManager::unloadFont(const std::string& fileName) {
    if (m_font.find(fileName) != m_font.end()) {
        TTF_CloseFont(m_font[fileName]);
        m_font.erase(fileName);
    }else{
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}

Mix_Music* ResourceManager::loadMusic(std::string fileName) {
    if (m_music.find(fileName) == m_music.end()) {
        Mix_Music *music = Mix_LoadMUS(fileName.c_str());
        if (music == nullptr) {
            std::cout << "Error: " << SDL_GetError() << std::endl;
        }
        m_music[fileName] = music;
    }
    return m_music[fileName];
}

void ResourceManager::unloadMusic(std::string fileName) {
    if (m_music.find(fileName) != m_music.end()) {
        Mix_FreeMusic(m_music[fileName]);
        m_music.erase(fileName);
    }else{
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}

Mix_Chunk* ResourceManager::loadSound(std::string fileName) {
    if (m_sound.find(fileName) == m_sound.end()) {
        Mix_Chunk *sound = Mix_LoadWAV(fileName.c_str());
        if (sound == nullptr) {
            std::cout << "Error: " << SDL_GetError() << std::endl;
        }
        m_sound[fileName] = sound;
    }
    return m_sound[fileName];
}

void ResourceManager::unloadSound(std::string fileName) {
    if (m_sound.find(fileName) != m_sound.end()) {
        Mix_FreeChunk(m_sound[fileName]);
        m_sound.erase(fileName);
    }else{
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture* ResourceManager::loadText(const std::string& define, const std::string& text, TTF_Font* font,
                                       int size, SDL_Color color) {
    if(m_text.find(define) != m_text.end()) {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

        if (surface == nullptr) {
            std::cout << "Error: " << SDL_GetError() << std::endl;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
        m_text[define] = texture;
    }
    return m_text[define];

}

void ResourceManager::start(SDL_Renderer *renderer) {
    m_renderer = renderer;
}

void ResourceManager::shutdown() {
    for (auto &texture : m_texture) {
        SDL_DestroyTexture(texture.second);
    }
    for (auto &font : m_font) {
        TTF_CloseFont(font.second);
    }
    for (auto &music : m_music) {
        Mix_FreeMusic(music.second);
    }
    for (auto &sound : m_sound) {
        Mix_FreeChunk(sound.second);
    }
    for (auto &text : m_text) {
        SDL_DestroyTexture(text.second);
    }
    m_texture.clear();
    m_font.clear();
    m_music.clear();
    m_sound.clear();
    m_text.clear();
}





