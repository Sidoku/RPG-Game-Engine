//
// Created by Sanjana Nalawade on 4/17/23.
//
#include "../include/GameOverScreen.h"
#include <iostream>
GameOverScreen::GameOverScreen(SDL_Renderer* renderer, int w, int h, SDL_Window* window)
        : mRenderer(renderer), mWindow(window), gameState(false){
    SDL_Surface* GameOverScreenSurface = SDL_LoadBMP("../Engine/assets/images/gameOver.bmp");
    mGameOverScreenTexture = SDL_CreateTextureFromSurface(renderer, GameOverScreenSurface);
    SDL_FreeSurface(GameOverScreenSurface);

    mGameOverScreenRect.x = 0;
    mGameOverScreenRect.y = 0;
    mGameOverScreenRect.w = w;
    mGameOverScreenRect.h = h;
//    mGameOverScreenRect.w = gamePixel * model->getCaveList().size();
//    mGameOverScreenRect.h = gamePixel * model->getCaveList()[0].size();
}

GameOverScreen::~GameOverScreen() {
    SDL_DestroyTexture(mGameOverScreenTexture);
}

void GameOverScreen::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, mGameOverScreenTexture, nullptr, &mGameOverScreenRect);
    SDL_RenderPresent(renderer);
}

bool GameOverScreen::Update() {
    SDL_Event e;
    bool keyPressed = false;
    while (!keyPressed) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    // std::cout << "ask to quit" << std::endl;
                    mGameStarted = false;
                    keyPressed = true;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                            case SDLK_s:
                                std::cout << "Pressed S" << std::endl;
                                mGameStarted = true;
                                keyPressed = true;
                                break;
                            case SDLK_q:
                                std::cout << "Pressed Q" << std::endl;
                                mGameStarted = false;
                                keyPressed = true;
                                break;
                    }
            }
             std::cout<<"Key Pressed"<< keyPressed << std::endl;
            }
            if (keyPressed) {
                break;
            }

        }
    return mGameStarted;
}
