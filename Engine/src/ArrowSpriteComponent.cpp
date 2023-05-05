#include "../include/ArrowSpriteComponent.hpp"
#include <iostream>




ArrowSpriteComponent::ArrowSpriteComponent(TransformComponent* transformComponent, int pix) : m_transformComponent(transformComponent), arrowPixel(pix)
{

}

ArrowSpriteComponent::~ArrowSpriteComponent(){
//// TODO: Make sure spritesheet and mTexture are destroyed
//// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void ArrowSpriteComponent::SetPosition(std::vector<int> caveId, std::vector<int> x, std::vector<int> y){
//     // x = x+1;
//     // y = y+1;
//     Vec2D* mPosition;
//    mPosition->x = (y*64) + 30;
//    mPosition->y = (x*64) + 15;
//    map_mPosition.insert(std::make_pair(caveId,mPosition));
//   std::cout << "X : " << mPosition.x <<std::endl;
//    std::cout << "Y : " << mPosition.y <<std::endl;
    for (int i = 0; i < caveId.size(); i++){

        Vec2D* m = new Vec2D();

        m->x = x[i];
        m->y = y[i];


        arrow_map_mPosition.insert(std::make_pair(caveId[i],m));
    }



}

void ArrowSpriteComponent::Update(){

    // The part of the image that we want to render

//    if (m_transformComponent->GetLastX() - m_transformComponent->GetX() != 0){
//        mCurrentFrame++;
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
    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 1563;
    mSrc.h = 1169;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.
//    std::cout<< mPosition.x <<std::endl;
//    std::cout<< mPosition.y <<std::endl;

//    mDest.x = mPosition.x;

//    mDest.y = mPosition.y;
    int caveId = m_transformComponent->GetCaveId();
    if(caveId !=0){
        UnSetPosition(m_transformComponent->GetCaveId());
        m_transformComponent->resetCaveId();
    }
    mDest.w = arrowPixel/3;
    mDest.h = arrowPixel/3;


}

void ArrowSpriteComponent::UnSetPosition(int caveId){
    if(caveId !=0){
        arrow_map_mPosition.erase(caveId);
    }
}

void ArrowSpriteComponent::Render(SDL_Renderer* renderer){

   //SDL_RenderCopy(renderer, mTexture, &mSrc, &mDest);

//        for (SDL_Texture* texture : idle_textures) {
//            SDL_RenderCopy(renderer, texture, &mSrc, &mDest);
//
//        }
//        if(counter >= idle_textures.size()){
//            counter =0;
//        }
    //std::cout << "I am here:" << std::endl;
        for (const auto m : arrow_map_mPosition) {
          //  std::cout << "I am here:" << std::endl;
            mDest.x = m.second->y * arrowPixel + arrowPixel/4;
            mDest.y = m.second->x * arrowPixel +  arrowPixel/4;
            //std::cout << "X:" << mDest.x << std::endl;
            SDL_RenderCopy(renderer, arrowTexture, NULL, &mDest);


        }



//        counter++;



//    else if(render_type == "walk") {
//        if(counter >= walk_textures.size()){
//            counter =0;
//        }
//        SDL_RenderCopy(renderer, walk_textures.at(counter), &mSrc, &mDest);
//        counter++;
//    }

}

void ArrowSpriteComponent::setType(std::string type) {
    this->render_type = type;
}
void ArrowSpriteComponent::LoadImage(std::string arrowFile, SDL_Renderer* ren) {
    // Load Attack
    // Load Idle
//    for (int i = 0; i < 7; i++) {
        std::string file = "../Engine/assets/images/Arrow/" + arrowFile+ ".bmp";
        std::cout << file << std::endl;
        const char *filepath = file.c_str();
        mSpriteSheet = SDL_LoadBMP(filepath);
        if (nullptr == mSpriteSheet) {
            SDL_Log("Failed to allocate surface");

        }
        arrowTexture = SDL_CreateTextureFromSurface(ren, mSpriteSheet);
        // Load Death
        // Load Walk
//    for(int i=1; i<6; i++){
//        walk_textures.push_back(SDL_CreateTextureFromSurface(ren,  SDL_LoadBMP(("../Engine/assets/images/Player/" + playerCharacter + "/Walk/"+"walk"+std::to_string(i)+".bmp").c_str())));
//    }
    std::string fil1 = "../Engine/assets/images/sprite.bmp";
    mSpriteSheet = SDL_LoadBMP(fil1.c_str());
    if(nullptr == mSpriteSheet){
           SDL_Log("Failed to allocate surface");
    }else{
        SDL_Log("Allocated a bunch of memory to create identical game character");
        // Create a texture from our surface
        // Textures run faster and take advantage
        // of hardware acceleration
        mTexture = SDL_CreateTextureFromSurface(ren, mSpriteSheet);
    }
//    }
}
