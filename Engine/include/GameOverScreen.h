//
// Created by Sanjana Nalawade on 4/17/23.
//

#include <SDL.h>

#ifndef FINAL_GAMEOVERSCREEN_H
#define FINAL_GAMEOVERSCREEN_H

class GameOverScreen {
public:
    GameOverScreen(SDL_Renderer* renderer,  int w, int h, SDL_Window* window);
    ~GameOverScreen();
    void Render(SDL_Renderer* renderer);
    bool Update();

private:
    SDL_Renderer* mRenderer;
    SDL_Texture* mGameOverScreenTexture;
    SDL_Rect mGameOverScreenRect;
    SDL_Window* mWindow;
    bool gameState;
    bool mGameStarted;
};


#endif //FINAL_GAMEOVERSCREEN_H
