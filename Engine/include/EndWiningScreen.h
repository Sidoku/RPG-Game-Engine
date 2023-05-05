//
// Created by Sanjana Nalawade on 4/17/23.
//

#include <SDL.h>

#ifndef FINAL_ENDWINNINGSCREEN_H
#define FINAL_ENDWINNINGSCREEN_H

class EndWiningScreen {
public:
    EndWiningScreen(SDL_Renderer* renderer,  int w, int h, SDL_Window* window);
    ~EndWiningScreen();
    void Render(SDL_Renderer* renderer);
    bool Update();

private:
    SDL_Renderer* mRenderer;
    SDL_Texture* mEndWiningScreenTexture;
    SDL_Rect mEndWiningScreenRect;
    bool mGameStarted;
    SDL_Window* mWindow;
};


#endif //FINAL_ENDWINNINGSCREEN_H
