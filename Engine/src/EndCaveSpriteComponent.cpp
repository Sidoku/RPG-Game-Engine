#include "../include/EndCaveSpriteComponent.hpp"
#include <iostream>




EndCaveSpriteComponent::EndCaveSpriteComponent(int pix){
    goalPixel = pix;

}

EndCaveSpriteComponent::~EndCaveSpriteComponent(){
//// TODO: Make sure spritesheet and mTexture are destroyed
//// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void EndCaveSpriteComponent::SetPosition(int x, int y){
    mPosition.x = (y*goalPixel) + goalPixel/4;
    mPosition.y = (x*goalPixel) + goalPixel/4;
}



void EndCaveSpriteComponent::Update(){
    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 1563;
    mSrc.h = 1169;
    mDest.x = mPosition.x;
    mDest.y = mPosition.y;
//    mDest.w = goalPixel/3;
//    mDest.h = goalPixel/3;
    mDest.w = goalPixel/2;
   mDest.h = goalPixel/2;


}

void EndCaveSpriteComponent::Render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, NULL, &mDest);

}

void EndCaveSpriteComponent::setType(std::string type) {
    this->render_type = type;
}
void EndCaveSpriteComponent::LoadImage( SDL_Renderer* ren) {
    std::string file = "../Engine/assets/images/goal1.bmp";
    std::cout << file << std::endl;
    const char *filepath = file.c_str();
    mSpriteSheet = SDL_LoadBMP(filepath);
    if (nullptr == mSpriteSheet) {
        SDL_Log("Failed to allocate surface");

    }
    texture = SDL_CreateTextureFromSurface(ren, mSpriteSheet);

}
