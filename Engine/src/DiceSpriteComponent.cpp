#include "../include/DiceSpriteComponent.hpp"
#include <iostream>

DiceSpriteComponent::DiceSpriteComponent(TransformComponent *transformComponent, int pix, int x, int y)
: m_transformComponent(transformComponent), dicePixel(pix), boardRow(x), boardCol(y){}

DiceSpriteComponent::~DiceSpriteComponent()
{
    //// TODO: Make sure spritesheet and mTexture are destroyed
    //// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}




// Set the sprite position
void DiceSpriteComponent::SetPosition(int x, int y)
{
    // x : gamePixel
    mPosition.x = dicePixel * boardCol + 4 * x - dicePixel ;
    //mPosition.y = dicePixel * boardRow - 2 * dicePixel;
    mPosition.y = 0;
    //   std::cout << "X : " << mPosition.x <<std::endl;
    //    std::cout << "Y : " << mPosition.y <<std::endl;
}

void DiceSpriteComponent::Update()
{

    mSrc.x = 18;
    mSrc.y = 55;
    mSrc.w = 67;
    mSrc.h = 56;

    if(m_transformComponent->GetY() == 1) {
        setType("roll");
    } else {
        setType("stop");
    }
    mDest.x = mPosition.x;
    mDest.y = mPosition.y;
    mDest.w = dicePixel;
    mDest.h = dicePixel;
}

void DiceSpriteComponent::Render(SDL_Renderer *renderer)
{
        if(render_type == "roll"){
            if (counter >= dice_textures.size())
            {
                counter = 0;
            }
            // std::cout << "Cx: " << mDest.x << "Cy: " <<mDest.y << std::endl;
            SDL_RenderCopy(renderer, dice_textures.at(counter), NULL, &mDest);

            counter++;
        }
        else if(render_type == "stop") {
            m_roll = m_transformComponent->GetX();
            if(m_roll > 6) {
                m_roll =1;
            }
            //std::cout << "Rolled : " << m_roll << std::endl;
            SDL_RenderCopy(renderer, dice_textures.at(m_roll-1), NULL, &mDest);

        }
//    std::cout << "Rendering Dice" << std::endl ;


}

void DiceSpriteComponent::setType(std::string type)
{
    this->render_type = type;
}

void DiceSpriteComponent:: set_roll(int value) {
    m_roll = value;
}

void DiceSpriteComponent::LoadImage(std::string diceCharacter, SDL_Renderer *ren)
{
    // Load Attack
    // Load Idle

//    std::string file = "../Engine/assets/images/goal.bmp";
//    std::cout << file << std::endl;
//    const char *filepath = file.c_str();
//    mSpriteSheet = SDL_LoadBMP(filepath);
//    if (nullptr == mSpriteSheet)
//    {
//        SDL_Log("Failed to allocate surface");
//    }
//    dice_textures.push_back(SDL_CreateTextureFromSurface(ren, mSpriteSheet));
    for (int i = 1; i < 7; i++)
    {

        std::string file = "../Engine/assets/images/Dice/" + diceCharacter  + std::to_string(i) + ".bmp";
        std::cout << file << std::endl;
        const char *filepath = file.c_str();
        mSpriteSheet = SDL_LoadBMP(filepath);
        if (nullptr == mSpriteSheet)
        {
            SDL_Log("Failed to allocate surface");
        }
        dice_textures.push_back(SDL_CreateTextureFromSurface(ren, mSpriteSheet));
    }

        // Load Death
        // Load Walk
        //    for(int i=1; i<6; i++){
        //        walk_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(("../Engine/assets/images/Player/" + playerCharacter + "/Walk/"+"walk"+std::to_string(i)+".bmp").c_str())));
        //    }
        //    std::string file = "../Engine/assets/images/sprite.bmp";
        //    mSpriteSheet = SDL_LoadBMP(file.c_str());
        //    if(nullptr == mSpriteSheet){
        //           SDL_Log("Failed to allocate surface");
        //    }else{
        //        SDL_Log("Allocated a bunch of memory to create identical game character");
        //        // Create a texture from our surface
        //        // Textures run faster and take advantage
        //        // of hardware acceleration
        //        mTexture = SDL_CreateTextureFromSurface(ren, mSpriteSheet);
        //    }
}    
