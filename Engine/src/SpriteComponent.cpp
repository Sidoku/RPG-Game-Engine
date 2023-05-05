#include "../include/SpriteComponent.hpp"
#include <iostream>




SpriteComponent::SpriteComponent(TransformComponent* transformComponent, int pix) : m_transformComponent(transformComponent), characterPixel(pix){

}

SpriteComponent::~SpriteComponent(){
//// TODO: Make sure spritesheet and mTexture are destroyed
//// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void SpriteComponent::SetPosition(int x, int y){
     // x = x+1;
     // y = y+1;
    mPosition.x = (y*characterPixel) + characterPixel/8;
    mPosition.y = (x*characterPixel) - characterPixel/8;
//   std::cout << "X : " << mPosition.x <<std::endl;
//    std::cout << "Y : " << mPosition.y <<std::endl;
}

void SpriteComponent::Update(){

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
        mSrc.h = 128;
    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.
//    std::cout<< mPosition.x <<std::endl;
//    std::cout<< mPosition.y <<std::endl;
   // SetPosition(m_transformComponent->GetX(),m_transformComponent->GetY());
   if(render_type != "walk") {
       mDest.x = mPosition.x;
       mDest.y = mPosition.y;
   }

    mDest.w = characterPixel;
    mDest.h = characterPixel;

    this->render_type = m_transformComponent->GetAnimType();


}

void SpriteComponent::Render(SDL_Renderer* renderer){
  //  SDL_RenderCopy(renderer, mTexture, &mSrc, &mDest);
    static int frameCounter = 0;
    const int walkFrameSkip = 8; // Adjust this value to control the walking animation speed


    if(render_type == "idle"){
//        for (SDL_Texture* texture : idle_textures) {
//            SDL_RenderCopy(renderer, texture, &mSrc, &mDest);
//
//        }
        if(counter >= idle_textures.size()){
            counter =0;
        }
        SDL_RenderCopy(renderer, idle_textures.at(counter), NULL, &mDest);
        counter++;


    }
    else if(render_type == "walk") {

        Uint32 frameDuration = 7113; // Adjust this value to control the walking animation speed
        static Uint32 lastFrameTime = SDL_GetTicks();

        if (frameCounter % walkFrameSkip == 0){
            lastFrameTime = SDL_GetTicks();

            // movement in vertical (y) direction
            if (m_transformComponent->GetLastX() - m_transformComponent->GetX() == 0) {

                std::cout << "Updating walking animation frame, counter: " << counter << std::endl;


                for (float i = 0; i < 1; i += 0.5) {
                    if (counter >= walk_textures.size()) {
                        counter = 0;
                    }
                    if (m_transformComponent->GetLastX() > m_transformComponent->GetX()) {
                        mDest.x = mPosition.x - i;
                    } else {
                        mDest.x = mPosition.x + i;
                    }
                    std::cout << "X: " << mDest.x / 64 << "Y: " << mDest.y / 64 << std::endl;
                    SDL_RenderCopy(renderer, walk_textures.at(counter), NULL, &mDest);
                    SetPosition(mDest.x, mDest.y);

                    SDL_Delay(2);
                }
            } else if (m_transformComponent->GetLastY() - m_transformComponent->GetY() == 0) {

                std::cout << "Updating walking animation frame, counter: " << counter << std::endl;

                for (float i = 0; i < 1; i += 0.5) {
                    if (counter >= walk_textures.size()) {
                        counter = 0;
                    }
                    //move left
                    if (m_transformComponent->GetLastY() > m_transformComponent->GetY()) {
                        mDest.y = mPosition.y - i;
                    }
                        //move right
                    else {
                        mDest.y = mPosition.y + i;
                    }
                    std::cout << "X: " << mDest.x << "Y: " << mDest.y << std::endl;
                    SDL_RenderCopy(renderer, walk_textures.at(counter), NULL, &mDest);
                    SetPosition(mDest.x, mDest.y);
                    counter++;
                    SDL_Delay(2);
                }
            }
            counter++;
        }






//
//        //movement in vertical (y) direction
//        if(m_transformComponent->GetLastX() - m_transformComponent->GetX() == 0){
//            if(counter >= walk_textures.size()){
//                counter =0;
//            }
//            for(float i = 0; i< 1; i+= 0.5){
//
//                if(m_transformComponent->GetLastX() > m_transformComponent->GetX()) {
//                 mDest.x = mPosition.x - i;
//                }else{
//                    mDest.x = mPosition.x + i;
//                }
//                std::cout << "X: " << mDest.x/64 << "Y: " << mDest.y/64 <<std::endl;
//                SDL_RenderCopy(renderer, walk_textures.at(counter), NULL, &mDest);
//                SetPosition( mDest.x,mDest.y);
//                counter++;
//                SDL_Delay(2);
//            }
//
//        }

       //movement in horizontal (x) direction
//       else if(m_transformComponent->GetLastY() - m_transformComponent->GetY() == 0) {
//            if(counter >= walk_textures.size()){
//                counter =0;
//            }
//            for(float i = 0; i< 1; i+= 0.5) {
//
//                //move left
//                if(m_transformComponent->GetLastY() > m_transformComponent->GetY())
//                {
//                    mDest.y = mPosition.y - i;
//                }
//                //move right
//                else
//                {
//                    mDest.y = mPosition.y + i;
//                }
//                std::cout << "X: " << mDest.x << "Y: " << mDest.y <<std::endl;
//                SDL_RenderCopy(renderer, walk_textures.at(counter), NULL, &mDest);
//                SetPosition( mDest.x,mDest.y);
//                counter++;
//                SDL_Delay(2);
//            }
//
//        }

        SetPosition(m_transformComponent->GetX(),m_transformComponent->GetY());
        SDL_Delay(112);
        setType("idle");
        m_transformComponent->SetAnimType("idle");
    }
    else if(render_type == "attack_right") {
        if(counter >= attack_right_textures.size()){
            counter =0;
        }
        SDL_RenderCopy(renderer, attack_right_textures.at(counter), NULL, &mDest);
        counter++;
    }
    else if(render_type == "attack_left") {
        if(counter >= attack_left_textures.size()){
            counter =0;
        }
        SDL_RenderCopy(renderer, attack_left_textures.at(counter), NULL, &mDest);
        counter++;
    }

}

void SpriteComponent::setType(std::string type) {
    this->render_type = type;
    //this->render_type = m_transformComponent->GetAnimType();
}
void SpriteComponent::LoadImage(std::string playerCharacter, SDL_Renderer* ren){

    // Load Idle
    for(int i=1; i<12; i++){
        std::string file = "../Engine/assets/images/Player/" + playerCharacter + "/Idle/" + "idle" + std::to_string(i) + ".bmp";
        std::cout << file << std::endl;
         const char * filepath = file.c_str();

        idle_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(filepath)));
    }
    // Load Death
    for(int i=1; i<11; i++)
    {
        death_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(("../Engine/images/Player/" + playerCharacter + "/Death/"+"death"+std::to_string(i)+".bmp").c_str())));
    }

    //Load Attack_right
    for(int i = 0; i< 5; i++)
    {
        attack_right_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(("../Engine/assets/images/Player/" + playerCharacter + "/Attack/"+"attack"+std::to_string(i)+".bmp").c_str())));
    }
    //Load Attack_left
    for(int i = 0; i< 5; i++)
    {
        attack_left_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(("../Engine/assets/images/Player/" + playerCharacter + "/Attack_flipped/"+"attack"+std::to_string(i)+".bmp").c_str())));
    }
    // Load Walk
    for(int i=1; i<7; i++){
        walk_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(("../Engine/assets/images/Player/" + playerCharacter + "/Walk/"+"walk"+std::to_string(i)+".bmp").c_str())));
    }
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
