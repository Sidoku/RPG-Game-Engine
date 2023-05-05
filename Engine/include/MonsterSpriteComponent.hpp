#ifndef MSPRITE_H
#define MSPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "IGraphicsEngineRenderer.hpp"
#include "TinyMath.hpp"
#include "TransformComponent.hpp"
#include "Component.hpp"
#include <unordered_map>
#include <memory>

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class MonsterSpriteComponent : public Component{
public:

    MonsterSpriteComponent();
    /**
     * Constructor
     */
    MonsterSpriteComponent(TransformComponent* transformComponent, int pix);
    /**
     * Constructor
     */
    ~MonsterSpriteComponent();
    /**
     * Initialize the sprite
     */
    void SetPosition(std::vector<int> caveId, std::vector<int> x, std::vector<int> y);
    /**
     * Update the sprites position and frame
     */
    void Update() override;
    /**
     * Render the sprite
     */
    void Render(SDL_Renderer* renderer) override;
    /**
     * Load a sprite
     */
    void LoadImage(std::string monsterCharacter,SDL_Renderer* ren);
    void setType(std::string type);
    void UnSetPosition(int caveId);

private:
    TransformComponent* m_transformComponent;
    std::unordered_map<int, const Vec2D*> map_mPosition;
	unsigned int    mCurrentFrame{1};
	unsigned int    mLastFrame{7};
    // An SDL Surface contains pixel data to draw an image
	SDL_Surface*    mSpriteSheet =  nullptr;
	SDL_Texture*    mTexture     =  nullptr;
	SDL_Rect        mSrc;
	SDL_Rect        mDest;
    std::vector<SDL_Texture* > attack_textures;
    std::vector<SDL_Texture* > idle_textures;
    std::vector<SDL_Texture* > death_textures;
    std::vector<SDL_Texture* > walk_textures;
    std::string render_type;
    std::unordered_map<int, const Vec2D*> deadMonsters;
    int counter =0;
    int dcounter = 0;
    int monsterPixel;
    std::unordered_map<int, int> death_counter;
    std::vector<int> erasedDeadMonster;
};

#endif
