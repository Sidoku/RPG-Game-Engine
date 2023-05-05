#ifndef TILE_H
#define TILE_H

#include <string>
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "GameWorld/Cave.hpp"
#include "ResourceManager.hpp"
#include "IGraphicsEngineRenderer.hpp"

/**
 * This is a minimal implementation of a TileMap
 */
class TileMapComponent : public Component {
public:
    
    /**
     * Constructor for a tilemap
     */
    TileMapComponent( int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* rend, std::vector<std::vector <Cave*>> caveList, std::string theme);
    /**
     * Destructor for a tilemap
     */
    ~TileMapComponent();
    /**
     * Temporary function for generating a simple
     * map to display some tiles
     */
    void GenerateSimpleMap();
    /**
     * Function for printing text to console
     */
    void PrintMap();
    /**
     * Set the 'type' of tile at an x and y position
     */
    void SetTile(int x, int y, int type);
    /**
     * Return the tile type at an x and y position
     */
    int GetTileType(int x, int y);
    /**
     * Draw all of the tiles in the tilemap
     */
    void Render(SDL_Renderer* renderer) override;



private:
    // Dimensions of our TileMap and individual tiles.
    // Used for spiltting up the sprite sheet
    int m_Rows;
    int m_Cols;      
    // How big each tile is.
    int m_TileWidth;
    int m_TileHeight;
    // size of our tilemap
    int m_MapX;
    int m_MapY; 
    // Where our TileMap is rendered
    // An SDL Surface contains pixel data to draw our TileMap
//    SDL_Surface *m_TileSpriteSheet;

    // Stores our tile types
    int* m_Tiles;
    std::vector<std::vector <Cave*>> m_caveList;

    SDL_Texture *m_Texture1E;
    SDL_Texture *m_Texture1N;
    SDL_Texture *m_Texture1S;
    SDL_Texture *m_Texture1W;

    SDL_Texture *m_Texture2NE;
    SDL_Texture *m_Texture2NS;
    SDL_Texture *m_Texture2NW;
    SDL_Texture *m_Texture2SE;
    SDL_Texture *m_Texture2SW;
    SDL_Texture *m_Texture2WE;

    SDL_Texture *m_Texture3NES;
    SDL_Texture *m_Texture3NWE;
    SDL_Texture *m_Texture3NSW;
    SDL_Texture *m_Texture3SWE;

    std::unordered_map< std::string , SDL_Texture* > texture_map;
    SDL_Texture* fileNameFromPath(Cave* cave);
    SDL_Texture *texture;
    bool flag = false;


};

#endif
