//
// Created by Sanjana Nalawade on 4/17/23.
//
#include "../include/StartScreen.h"
#include <iostream>


StartScreen::StartScreen(SDL_Renderer* renderer, int w, int h, SDL_Window* window)
        : mWindow(window) {
    mStartScreenRect.w=w;
    mStartScreenRect.h=h;
    SDL_Surface* startScreenSurface = SDL_LoadBMP("../Engine/assets/images/startPage.bmp");
    mStartScreenTexture = SDL_CreateTextureFromSurface(renderer, startScreenSurface);
    SDL_FreeSurface(startScreenSurface);
    startScreenSurface = nullptr;
}


StartScreen::~StartScreen() {
    SDL_DestroyTexture(mStartScreenTexture);
}
void StartScreen::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, mStartScreenTexture, nullptr, &mStartScreenRect);
    SDL_RenderPresent(renderer);


}




bool StartScreen::Update() {

    SDL_Event e;
    bool keyPressed = false;
    while (!keyPressed) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    std::cout << "ask to quit" << std::endl;
                    mGameStarted = false;
                    keyPressed = true;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_s:
                            mGameStarted = true;
                            keyPressed = true;
                    }


            }
//            std::cout<<"break the inside while"<<std::endl;
        }
        if (keyPressed) {
            break;
        }

    }

    return mGameStarted;
}


//            if (e.type == SDL_QUIT) {
//                std::cout << "ask to quit" << std::endl;
//                mGameStarted = false;
//                std::cout << mGameStarted << std::endl;
//                return mGameStarted;
//            } else if (e.type == SDL_KEYDOWN) {
//                if (e.key.keysym.sym == SDLK_s) {
//                    std::cout << "ask to advance" << std::endl;
//                    mGameStarted = true;
//                    return mGameStarted;
//                }
//            }
//        }






