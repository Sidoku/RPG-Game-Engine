#include <iostream>
#include <iomanip>
#include <vector>
#include "../include/TileMapComponent.hpp"
#include <sstream>
// Creates a new tile map.
// rows and cols are how many different tiles there are in the sprite sheet
// 
// _TileWidth and _TileHeight are the size of each individual
// tile in the sprite sheet.
// (Typically this works best if they are square for this implementation.)
//
// _mapX, and _mapY are the size of the TileMapComponent. This is the actual
// number of tiles in the game that the player sees, not how many tiles
// are in the actual sprite sheet file loaded.
TileMapComponent::TileMapComponent( int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* renderer, std::vector<std::vector <Cave*>> caveList, std::string theme) : m_caveList(caveList){
    if(nullptr==renderer){
        SDL_Log("No valid renderer found");
    }


    // Setup variables
    m_TileWidth = _TileWidth;
    m_TileHeight = _TileHeight;

    m_MapX = _mapX;
    m_MapY = _mapY;
    std::cout << "Row : " << m_MapX << "Col: " << m_MapY << std::endl;
    // Load the TileMapComponent Image
    // This is the image that will get
    // sliced into smaller subsections of individual tiles.
 //   m_TileSpriteSheet = SDL_LoadBMP(tileSheetFileName.c_str());
//
//    if(nullptr == m_TileSpriteSheet){
//           SDL_Log("Failed to allocate surface"));
//    }else{
//        // Create a texture from our surface
//        // Textures run faster and take advantage of
//        //  hardware acceleration
//        m_Texture = SSDL_CreateTextureFromSurface(renderer, m_TileSpriteSheet);
//
//    }

// 64
// ______


   // texture = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP("../Engine/assets/images/Tiles.bmp"));
    m_Texture1E = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/1/1E.bmp").c_str())); //1
    m_Texture1N = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/1/1N.bmp").c_str())); //2
    m_Texture1S = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/1/1S.bmp").c_str())); //3
    m_Texture1W = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/1/1W.bmp").c_str())); //4

    m_Texture2NE = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/2/2NE.bmp").c_str())); //5
    m_Texture2NS = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/2/2NS.bmp").c_str())); //6
    m_Texture2NW = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/2/2NW.bmp").c_str())); //7
    m_Texture2SE = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/2/2SE.bmp").c_str())); //8
    m_Texture2SW = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/2/2SW.bmp").c_str())); //9
    m_Texture2WE = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/2/2WE.bmp").c_str())); //10


    m_Texture3NES = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/3/3NES.bmp").c_str())); //11
    m_Texture3NWE = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/3/3NWE.bmp").c_str())); //12
    m_Texture3NSW = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/3/3NSW.bmp").c_str())); //13
    m_Texture3SWE = SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/3/3SWE.bmp").c_str())); //14

    SDL_Texture *m_Texture4NSEW = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(("../Engine/assets/images/tiles/"+theme+"/4/4NSEW.bmp").c_str()));

    texture_map.insert(std::make_pair("1E", m_Texture1E));
    texture_map.insert(std::make_pair("1N", m_Texture1N));
    texture_map.insert(std::make_pair("1S", m_Texture1S));
    texture_map.insert(std::make_pair("1W", m_Texture1W));

    texture_map.insert(std::make_pair("2EN", m_Texture2NE));
    texture_map.insert(std::make_pair("2NS", m_Texture2NS));
    texture_map.insert(std::make_pair("2NW", m_Texture2NW));
    texture_map.insert(std::make_pair("2ES", m_Texture2SE));
    texture_map.insert(std::make_pair("2SW", m_Texture2SW));
    texture_map.insert(std::make_pair("2EW", m_Texture2WE));

    texture_map.insert(std::make_pair("3ENS", m_Texture3NES));
    texture_map.insert(std::make_pair("3ENW", m_Texture3NWE));
    texture_map.insert(std::make_pair("3NSW", m_Texture3NSW));
    texture_map.insert(std::make_pair("3ESW", m_Texture3SWE));

    texture_map.insert(std::make_pair("4ENSW", m_Texture4NSEW));


    // Setup the TileMapComponent array
    // This sets each tile to '0'
    m_Tiles = new int[m_MapX*m_MapY];
    for(int i=0; i < m_MapX*m_MapY; i++){
        m_Tiles[i] = -1; // Default value is no tile.
    }

}

// Destructor
TileMapComponent::~TileMapComponent(){
    SDL_DestroyTexture(m_Texture1E);
    // Remove our TileMapComponent
    delete[] m_Tiles;
}

// Helper function to gegenerate a simlpe map
void TileMapComponent::GenerateSimpleMap(){
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
           if(y==0){ 
                SetTile(x,y,12);
           }
           if(y==m_MapY-1){ 
                SetTile(x,y,0);
           }
       }
    }
}

// Helper function to print out the tile map
// to the console
void TileMapComponent::PrintMap(){
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
            std::cout << std::setw(3) << GetTileType(x,y);
       }
         std::cout << "\n";
    }
}



void TileMapComponent::SetTile(int x, int y, int type){
    m_Tiles[y * m_MapX + x] = type;
}


// Returns what the tile is at a specific position.
int TileMapComponent::GetTileType(int x, int y){
    return m_Tiles[y * m_MapX + x];
}

// render TileMapComponent
void TileMapComponent::Render(SDL_Renderer* renderer){
    if(nullptr==renderer){
        SDL_Log("No valid renderer found");
    }

        SDL_Rect Src, Dest;

        for (int y = 0; y < m_MapX; y++) {
            for (int x = 0; x < m_MapY; x++) {

                Src.x = 0;
                Src.y = 0;
                Src.w = m_TileWidth;
                Src.h = m_TileHeight;

                // Render our Tile at this location
                Dest.x = x * m_TileWidth;
                Dest.y = y * m_TileWidth;
                Dest.w = m_TileWidth;
                Dest.h = m_TileHeight;

                SDL_Texture *tile_texture = fileNameFromPath(m_caveList.at(y).at(x));
                SDL_RenderCopy(renderer, tile_texture, NULL, &Dest);

                // }
            }
        }


}


SDL_Texture* TileMapComponent::fileNameFromPath(Cave* cave) {
    std::stringstream res_fileName;
    //res_fileName << "m_texture";
    std::stringstream fileName;
    int count=0;
    for (auto& pair : cave->getDirection()) {
        if (pair.second !=0 ) {
            std::string d = pair.first;
            if(d=="EAST") {
                fileName << "E";
            }
            if(d == "NORTH") {
                fileName << "N";
            }
            if(d== "SOUTH") {
                fileName << "S";
            }
            if(d == "WEST") {
                fileName << "W";
            }
            count++;
        }
    }


    res_fileName << count;
    res_fileName << fileName.str();

    if (texture_map.find(res_fileName.str()) != texture_map.end()) {
        texture = texture_map.find(res_fileName.str())->second;
    }
    return texture;

};

