#ifndef DSPRITE_HPP
#define DSPRITE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "IGraphicsEngineRenderer.hpp"
#include "TinyMath.hpp"
#include "TransformComponent.hpp"
#include "Component.hpp"
#include <unordered_map>
#include "GameWorld/Random.h"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class DiceSpriteComponent : public Component {
public:
    DiceSpriteComponent();
    /**
     * Constructor
     */
    DiceSpriteComponent(TransformComponent *transformComponent, int pix, int x, int y);
    /**
     * Constructor
     */
    ~DiceSpriteComponent();
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
    void Render(SDL_Renderer *renderer) override;
    /**
     * Load a sprite
     */
    void LoadImage(std::string diceCharacter, SDL_Renderer *ren);
    void setType(std::string type);

    /**
     * Roll the dice and return a random number between 1 and 6
     */
    void set_roll(int value);

private:
    TransformComponent *m_transformComponent;
    Vec2D mPosition;
    unsigned int mCurrentFrame{1};
    unsigned int mLastFrame{7};
    // An SDL Surface contains pixel data to draw an image
    SDL_Surface *mSpriteSheet = nullptr;
    SDL_Texture *mTexture = nullptr;
    SDL_Rect mSrc;
    SDL_Rect mDest;
    std::vector<SDL_Texture *> dice_textures;
    std::string render_type;
    int counter = 0;
    int m_roll = 0;
    int dicePixel;
    int boardRow;
    int boardCol;

    /* std::vector<SDL_Texture *> idle_textures;
    std::vector<SDL_Texture *> death_textures;
    std::vector<SDL_Texture *> walk_textures; */
    };

#endif
