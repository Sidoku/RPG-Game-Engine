//
// Created by Sanjana Nalawade on 4/17/23.
//
#include "../include/EndWiningScreen.h"

EndWiningScreen::EndWiningScreen(SDL_Renderer* renderer, int w, int h, SDL_Window* window)
        : mRenderer(renderer), mWindow(window){
    SDL_Surface* EndWiningScreenSurface = SDL_LoadBMP("../Engine/assets/images/winning.bmp");
    mEndWiningScreenTexture = SDL_CreateTextureFromSurface(renderer, EndWiningScreenSurface);
    SDL_FreeSurface(EndWiningScreenSurface);

    mEndWiningScreenRect.x = 0;
    mEndWiningScreenRect.y = 0;
    mEndWiningScreenRect.w = w;
    mEndWiningScreenRect.h = h;
//    mEndWiningScreenRect.w = gamePixel * model->getCaveList().size();
//    mEndWiningScreenRect.h = gamePixel * model->getCaveList()[0].size();
}

EndWiningScreen::~EndWiningScreen() {
    SDL_DestroyTexture(mEndWiningScreenTexture);
}

void EndWiningScreen::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, mEndWiningScreenTexture, nullptr, &mEndWiningScreenRect);
    SDL_RenderPresent(renderer);
}

bool EndWiningScreen::Update() {
    SDL_Event e;
    bool keyPressed = false;
    while (!keyPressed) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    //std::cout << "ask to quit" << std::endl;
                    mGameStarted = false;
                    keyPressed = true;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                            case SDLK_s:
                                mGameStarted = true;
                                keyPressed = true;
                                break;
                            case SDLK_q :
                                mGameStarted = false;
                                keyPressed = true;
                                break;
                        }
                    }

            }
            if (keyPressed) {
                break;
            }

        }
    return mGameStarted;
}