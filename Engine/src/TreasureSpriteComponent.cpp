#include "../include/TreasureSpriteComponent.hpp"
#include <iostream>


TreasureSpriteComponent::TreasureSpriteComponent(TransformComponent *transformComponent, int pix)
        : m_transformComponent(transformComponent), treasurePixel(pix) {

}

TreasureSpriteComponent::~TreasureSpriteComponent() {
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void TreasureSpriteComponent::SetPosition(std::vector<int> caveId, std::vector<int> x, std::vector<int> y) {
    for (int i = 0; i < caveId.size(); i++) {
        Vec2D *m = new Vec2D();
        m->x = x[i];
        m->y = y[i];

        treasure_map_mPosition.insert(std::make_pair(caveId[i], m));
    }
}

void TreasureSpriteComponent::UnSetPosition(int caveId) {
    if (caveId != 0) {
        treasure_map_mPosition.erase(caveId);
    }
}

void TreasureSpriteComponent::Update() {
    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = 1563;
    mSrc.h = 1169;
    int caveId = m_transformComponent->GetCaveId();
    if (caveId != 0) {
        UnSetPosition(m_transformComponent->GetCaveId());
        m_transformComponent->resetCaveId();
    }

    mDest.w = treasurePixel / 3;
    mDest.h = treasurePixel / 3;


}

void TreasureSpriteComponent::Render(SDL_Renderer *renderer) {
        for (const auto m: treasure_map_mPosition) {
            mDest.x = m.second->y * treasurePixel + treasurePixel / 4;
            mDest.y = m.second->x * treasurePixel + treasurePixel / 4;
            SDL_RenderCopy(renderer, treasureTexture, NULL, &mDest);

        }
}

void TreasureSpriteComponent::setType(std::string type) {
    this->render_type = type;
}

void TreasureSpriteComponent::LoadImage(std::string treasureFile, SDL_Renderer *ren) {
    std::string file = "../Engine/assets/images/Treasure/" + treasureFile + ".bmp";
    std::cout << file << std::endl;
    const char *filepath = file.c_str();
    mSpriteSheet = SDL_LoadBMP(filepath);
    if (nullptr == mSpriteSheet) {
        SDL_Log("Failed to allocate surface");

    }
    treasureTexture = SDL_CreateTextureFromSurface(ren, mSpriteSheet);

}
