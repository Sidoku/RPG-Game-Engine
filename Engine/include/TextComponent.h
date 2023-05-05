//
// Created by Sanjana Nalawade on 4/17/23.
//

#ifndef FINAL_TEXTCOMPONENT_H
#define FINAL_TEXTCOMPONENT_H

#include <iostream>
#include "TinyMath.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include <SDL_ttf.h>
#include <sstream>

class TextComponent : public Component {
public:

    TextComponent();

    TextComponent(TransformComponent* transformComponent, int pix);
    // destructor
    ~TextComponent();


    void SetPosition(int x, int y);
    /**
     * Update the sprites position and frame
     */
    void Update() override;
    /**
     * Render the sprite
     */
    void Render(SDL_Renderer* renderer) override;

    void LoadFont(std::string fileName,int fontSize, SDL_Renderer*);

    // function to set the score of the game
    void setText(std::string text);


private:

    SDL_Renderer *renderer; // renderer is used for drawing the score board on the screen
    TTF_Font *font; // font is used for setting the font of the score
    SDL_Surface *surface{}; // surface is used for creating the texture of the score
    SDL_Texture *texture{}; // texture is used for displaying the score
    SDL_Rect        mSrc;
    SDL_Rect        mDest;
    Vec2D           mPosition;
    TransformComponent  *m_transformComponent;
    int textPixel;
    std::string text;
    int boardRow;
    int boardCol;
    SDL_Renderer* ren;
    std::stringstream instruct;
};


#endif //FINAL_TEXTCOMPONENT_H
