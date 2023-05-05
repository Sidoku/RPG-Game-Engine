#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include "../include/GameObject.hpp"
#include "TinyMath.hpp"
#include "IGraphicsEngineRenderer.hpp"
#include "GameWorld/GameModel.h"
#include "ArrowSpriteComponent.hpp"
#include "TreasureSpriteComponent.hpp"
#include "EndCaveSpriteComponent.hpp"
#include "DiceSpriteComponent.hpp"
#include "AudioComponent.hpp"
#include "TextComponent.h"
#include "StartScreen.h"
#include "EndWiningScreen.h"
#include "GameOverScreen.h"
/**
 * This class sets up the main game engine
 */
class Engine{
public:
    /**
     * Constructor of Engine
     */
    Engine(GameModel* model);
    /**
     * Destructor
     */
    ~Engine();
    /**
     * Input engine
     */
    void Input(bool *quit);
    /**
     * Per frame update
     */
    void Update();
    /**
     * Per frame render. Renders everything
     */
    void Render();
    /**
     * Main Game Loop that runs forever
     */
    bool MainGameLoop();

    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Start' to launch the engine
     */
    void Start();

    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();

    /**
     * Request to startup the Graphics Subsystem
     */
	void InitializeGraphicsSubSystem(int w, int h, std::string tileImg, std::string playerImg, std::string monsterImg);


    bool renderStartScreen(bool *quit);




private:
    // Engine Subsystem
    // Setup the Graphics Rendering Engine
    IGraphicsEngineRenderer* mRenderer = nullptr;
    GameObject character;
    GameObject monsters;
    GameObject treasure;
    GameObject arrow;
    GameObject endCave;
    GameObject dice;
    GameObject text;
    GameObject instructionstxt;
    GameModel* model;
    StartScreen* startScreen;
    std::vector<GameObject> m_gameObjects;
    std::string playerCharacter;
    Cave* calculatePlayerPosition();
    void caluclateLocations();
    // Monster
    std::vector<int> monsterCaveID;
    std::vector<int> monsterX;
    std::vector<int> monsterY;
    // Treasure
    std::vector<int> treasureCaveID;
    std::vector<int> treasureX;
    std::vector<int> treasureY;
    // Arrow
    std::vector<int> arrowCaveID;
    std::vector<int> arrowX;
    std::vector<int> arrowY;
    int gamePixel;
    int row;
    int col;
    bool startgame = false;
    TextComponent* textComponent;
    SDL_Renderer* renderer;
    SDL_Window* window;
    std::string tilesImg;
    std::string playerImg;
    std::string monsterImg;

};





#endif
