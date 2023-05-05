#include "../include/MonsterSpriteComponent.hpp"
#include <iostream>




MonsterSpriteComponent::MonsterSpriteComponent(TransformComponent* transformComponent, int pix) : m_transformComponent(transformComponent), monsterPixel(pix){

}

MonsterSpriteComponent::~MonsterSpriteComponent(){
//// TODO: Make sure spritesheet and mTexture are destroyed
//// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void MonsterSpriteComponent::SetPosition(std::vector<int> caveId, std::vector<int> x, std::vector<int> y){
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


        map_mPosition.insert(std::make_pair(caveId[i],m));
    }

}

void MonsterSpriteComponent::UnSetPosition(int caveId){
    if(caveId !=0){
        auto it = map_mPosition.find(caveId);
         if (it != map_mPosition.end()) {
            deadMonsters.insert(std::make_pair(it->first, it->second));
            death_counter.insert(std::make_pair(it->first, 50));
            }
        map_mPosition.erase(caveId);
    }
}


void MonsterSpriteComponent::Update(){


    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 1563;
    mSrc.h = 1169;
    int caveId = m_transformComponent->GetCaveId();
    if(caveId !=0){
        UnSetPosition(m_transformComponent->GetCaveId());
        m_transformComponent->resetCaveId();
    }

    mDest.w = monsterPixel/2 ;
    mDest.h = monsterPixel/2 ;


}

void MonsterSpriteComponent::Render(SDL_Renderer* renderer){
    render_type = m_transformComponent->GetAnimType();
    if(render_type == "idle"){
        if(counter >= idle_textures.size()){
            
            counter =0;
        }
        for (const auto m : map_mPosition) {
            mDest.x = m.second->y * monsterPixel + monsterPixel/4 ;
            mDest.y = m.second->x * monsterPixel + monsterPixel/4;

            SDL_RenderCopy(renderer, idle_textures.at(counter), NULL, &mDest);


        }
        counter++;
    }
    if( deadMonsters.size() > 0)
    {
         for (const auto m : deadMonsters) {
                 mDest.x = m.second->y * monsterPixel + monsterPixel/4 ;
                 mDest.y = m.second->x * monsterPixel + monsterPixel/4;
                SDL_Delay(15);
                if(dcounter < 5){
                    SDL_RenderCopy(renderer, death_textures.at(dcounter), NULL, &mDest);
                } else {
                    SDL_RenderCopy(renderer, death_textures.at(6), NULL, &mDest);
                }
                death_counter[m.first]--;
                if(death_counter[m.first] <= 0)
                {
                    erasedDeadMonster.push_back(m.first);

                }
             //std::cout << "Counter  :" << death_counter[m.first] << std::endl;

            }


        if(dcounter < death_textures.size()) {
            dcounter++;
        } else if (dcounter >= death_textures.size()){
                dcounter = 6;
        }

    }
    if(erasedDeadMonster.size() > 0)
    {
        for(int i : erasedDeadMonster){
            deadMonsters.erase(i);
        }
    }

}

void MonsterSpriteComponent::setType(std::string type) {
    this->render_type = type;
    m_transformComponent->SetAnimType(type);
}
void MonsterSpriteComponent::LoadImage(std::string monsterCharacter, SDL_Renderer* ren) {
    // Load Attack
    for (int i = 0; i < 7; i++) {
        std::string file =
                "../Engine/assets/images/Monster/" + monsterCharacter + "/Attack/" + "ATTAK_00" + std::to_string(i) + ".bmp";
        std::cout << file << std::endl;
        const char *filepath = file.c_str();
        mSpriteSheet = SDL_LoadBMP(filepath);
        if (nullptr == mSpriteSheet) {
            SDL_Log("Failed to allocate surface");

        }
    }
        attack_textures.push_back(SDL_CreateTextureFromSurface(ren, mSpriteSheet));
    // Load Idle
    for (int i = 0; i < 7; i++) {
        std::string file =
                "../Engine/assets/images/Monster/" + monsterCharacter + "/idle/" + "IDLE_00" + std::to_string(i) + ".bmp";
        std::cout << file << std::endl;
        const char *filepath = file.c_str();
        mSpriteSheet = SDL_LoadBMP(filepath);
        if (nullptr == mSpriteSheet) {
            SDL_Log("Failed to allocate surface");

        }
        idle_textures.push_back(SDL_CreateTextureFromSurface(ren, mSpriteSheet));

        // Load Death
for (int i = 0; i < 7; i++) {
        std::string file =
                "../Engine/assets/images/Monster/" + monsterCharacter + "/Die/" + "DIE_00" + std::to_string(i) + ".bmp";
        std::cout << file << std::endl;
        const char *filepath = file.c_str();
        mSpriteSheet = SDL_LoadBMP(filepath);
        if (nullptr == mSpriteSheet) {
            SDL_Log("Failed to allocate surface");

        }
        death_textures.push_back(SDL_CreateTextureFromSurface(ren, mSpriteSheet));
}

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
}
