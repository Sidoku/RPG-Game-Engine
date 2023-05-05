//
// Created by Sanjana Nalawade on 4/17/23.
//



#ifndef FINAL_STARTSCREEN_H
#define FINAL_STARTSCREEN_H

#include <SDL.h>
#include "TransformComponent.hpp"
class StartScreen {
public:

    StartScreen(SDL_Renderer* renderer,  int w, int h, SDL_Window* window);
    ~StartScreen();
    void Render(SDL_Renderer* renderer);
    bool Update();

private:
    SDL_Surface* startScreenSurface;
    SDL_Texture* mStartScreenTexture;
    SDL_Rect mStartScreenRect;
    bool mGameStarted;
    SDL_Window* mWindow;
};


#endif //FINAL_STARTSCREEN_H