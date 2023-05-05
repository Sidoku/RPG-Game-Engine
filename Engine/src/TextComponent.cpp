//
// Created by Sanjana Nalawade on 4/17/23.
//

#include "../include/TextComponent.h"
#include <iostream>




TextComponent::TextComponent(TransformComponent* transformComponent, int pix) : m_transformComponent(transformComponent), textPixel(pix){
    TTF_Init();
//    instruct << "___________\n Instructions : \n___________\n"
//             << "1. Use WASD or Arrow keys to move around the game world.\n"
//             << "2. To perform actions, you need to roll dice. The dice roll determines the number of actions you can perform in that turn.\n"
//             <<   "3. Press the \"R\" key to pick up the Axe.\n"
//             <<   "4. You must have the Axe to defeat the monsters. Each monster requires 1 or 2 axe kills to die.\n"
//             <<   "5. Press spacebar to enter attack stance and then press the direction key to attack in that direction.\n"
//             <<   "6. Press the \"T\" key to pick up treasure.\n"
//             <<   "7. The game includes a maze, and your objective is to reach the end level door without getting killed by monsters.";
    instruct <<  "______________\n Instructions : \n______________\n"
                 "1. Move with WASD/Arrow keys.\n"
                "2. Roll dice for actions (L).\n"
                "3. Pick up Axe (R) to defeat monsters\n(1-2 axe kills per monster).\n"
                "4. Press space to enter attack stance, then direction key to attack.\n"
                "5. Collect treasure (P).\n"
                "6. Reach the end level door without getting killed.";
}

TextComponent::~TextComponent(){
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();

}

// Set the sprite position
void TextComponent::SetPosition(int x, int y){
    this->boardRow=x;
    this->boardCol=y;
    mPosition.x = textPixel * boardCol +10;
    mPosition.y = 0;
//    // x = x+1;
//    // y = y+1;
//    mPosition.x = (y*characterPixel) + characterPixel/8;
//    mPosition.y = (x*characterPixel) - characterPixel/8;
////   std::cout << "X : " << mPosition.x <<std::endl;
////    std::cout << "Y : " << mPosition.y <<std::endl;
}

void TextComponent::Update(){

    // The part of the image that we want to render

//    if (m_transformComponent->GetLastX() - m_transformComponent->GetX() != 0){
//        mCurrentFrame++;
//    }
//
//
//    if(mCurrentFrame>6){
//        mCurrentFrame=0;
//
//
//    }
    // SetPosition(m_transformComponent->GetX(),m_transformComponent->GetY());
    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
//    mSrc.x = mCurrentFrame*75;
//    mSrc.y = 0;
//    mSrc.w = 75;
//    mSrc.h = 87;
//    std::cout << "This x : " << m_transformComponent->GetX() << std::endl;
//    std::cout << "LAST X : " << m_transformComponent->m_lastPosition.x << std::endl;
//    std::cout << "------------------------------" << std::endl;
//    mSrc.x = 18;
//    mSrc.y = 55;
//    mSrc.w = 67;
//    mSrc.h = 56;
    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 128;
    mSrc.h = boardCol*textPixel;
    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.
//    std::cout<< mPosition.x <<std::endl;
//    std::cout<< mPosition.y <<std::endl;
    //SetPosition(m_transformComponent->GetX(),m_transformComponent->GetY());
    setText(m_transformComponent->getDetailsText());
    mDest.x = mPosition.x;
    mDest.y = mPosition.y;
    mDest.w = textPixel;
    mDest.h = textPixel;


}

void TextComponent::Render(SDL_Renderer* renderer){
    //  SDL_RenderCopy(renderer, mTexture, &mSrc, &mDest);
   // int width, int height
    SDL_QueryTexture(texture, nullptr, nullptr, &mDest.w, &mDest.h);
    SDL_RenderCopy(renderer, texture, nullptr, &mDest);
//    if(render_type == "idle"){
////        for (SDL_Texture* texture : idle_textures) {
////            SDL_RenderCopy(renderer, texture, &mSrc, &mDest);
////
////        }
//        if(counter >= idle_textures.size()){
//            counter =0;
//        }
//        SDL_RenderCopy(renderer, idle_textures.at(counter), NULL, &mDest);
//        counter++;
//
//
//    }
//    else if(render_type == "walk") {
//        if(counter >= walk_textures.size()){
//            counter =0;
//        }
//        SDL_RenderCopy(renderer, walk_textures.at(counter), NULL, &mDest);
//        counter++;
//    }

}

void TextComponent::setText(std::string text) {
//    SDL_FreeSurface(surface);
//    SDL_DestroyTexture(texture);
    // this->text = text;
//    surface = TTF_RenderText_Solid(font, text.c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
//    texture = SDL_CreateTextureFromSurface(ren, surface);
    std:: string concatText = text + "\n" + instruct.str();
    //std::cout << concatText;
    this->text = concatText;

    // Free the existing surface and texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Create a new surface and texture with the updated text
   // std::cout << text << std::endl;
    // Remove newline characters from the text
   // text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());

    surface = TTF_RenderText_Blended_Wrapped(font, this->text.c_str(), {0xFF, 0xFF, 0xFF, 0xFF}, (text.size()*2) );
    texture = SDL_CreateTextureFromSurface(ren, surface);

    // Retrieve the width and height of the new texture
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    // Update the destination rectangle for rendering
    mDest.w = width;
    mDest.h = height;

}
void TextComponent::LoadFont(std::string fileName, int fontsize, SDL_Renderer* ren) {
    font = TTF_OpenFont("../Engine/assets/fonts/ModernWarfare-OV7KP.ttf", fontsize);
    //font = TTF_OpenFont((fileName+".ttf").c_str(), 40);
    surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
    texture = SDL_CreateTextureFromSurface(ren, surface);
    this->ren = ren;
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);


}
