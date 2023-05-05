#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "IGraphicsEngineRenderer.hpp"
#include "TinyMath.hpp"
#include "TransformComponent.hpp"
#include "Component.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteComponent : public Component{
public:

    SpriteComponent();
    /**
     * Constructor
     */
    SpriteComponent(TransformComponent* transformComponent, int pix);
    /**
     * Constructor
     */
    ~SpriteComponent();
    /**
     * Initialize the sprite
     */
    void SetPosition(int x, int y);
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
    void LoadImage(std::string playerCharacter,SDL_Renderer* ren);
    void setType(std::string type);

private:
    TransformComponent* m_transformComponent;
    Vec2D           mPosition;
	unsigned int    mCurrentFrame{1};
	unsigned int    mLastFrame{7};
    // An SDL Surface contains pixel data to draw an image
	SDL_Surface*    mSpriteSheet =  nullptr;
	SDL_Texture*    mTexture     =  nullptr;
	SDL_Rect        mSrc;
	SDL_Rect        mDest;
    std::vector<SDL_Texture* > attack_right_textures;
    std::vector<SDL_Texture* > attack_left_textures;
    std::vector<SDL_Texture* > idle_textures;
    std::vector<SDL_Texture* > death_textures;
    std::vector<SDL_Texture* > walk_textures;
    std::string render_type;
    int counter =0;
    int characterPixel;
    float anim_delay = 0.25;
};

#endif
