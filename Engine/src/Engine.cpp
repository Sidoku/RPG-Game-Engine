#include "../include/Engine.hpp"
#include "../include/SpriteComponent.hpp"
#include "../include/TileMapComponent.hpp"
#include "../include/ControllerComponent.hpp"
#include "../include/MonsterSpriteComponent.hpp"


#include <memory>


// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>
//// Try toggling this number!
//#define CHARACTERS 1
//
//
//// Global array to create our characters
//SpriteComponent characters[CHARACTERS];


// Create a TileMap
TileMapComponent* myTileMap;

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine(GameModel* model) : model(model) {
    gamePixel = model->getPix();
}


// Proper shutdown and destroy initialized objects
Engine::~Engine(){
}

// Return Input
void Engine::Input(bool *quit){
   //  std::cout << "In Input \n";
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          *quit = true;
        } else if (e.type == SDL_KEYDOWN) {
//            if (e.key.keysym.sym == SDLK_s) {
//               startgame = true;
//            }
//            else if(e.key.keysym.sym == SDLK_q) {
//                *quit = true;
//            }
        }
      }
}

// Update SDL
void Engine::Update()

{
//    std::cout << "In Update\n";
    static int frame =0 ;
    // Increment the frame that
    // the sprite is playing
    frame++;
    if(frame>6){
        frame=0;
    }


    for (auto gameObject : m_gameObjects) {
        gameObject.Update();
    }

}




// Render
// The render function gets called once per loop
void Engine::Render(){

    // Clear the screen
    mRenderer->SetRenderDrawColor(0, 0, 0, 255);
    mRenderer->RenderClear();

    // Render all game objects
    for (auto gameObject : m_gameObjects) {
        gameObject.Render(mRenderer->GetRenderer());
    }

    // Flip the buffer
    mRenderer->RenderPresent();
}



//Loops forever!
bool Engine::MainGameLoop() {
    // std::cout << "In Main\n";
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;

    bool flag = false;
    startScreen->Render(renderer);
    while (!flag) {

        SDL_Delay(100);
//         To prevent high CPU usage, add a short delay
        flag = startScreen->Update();
        std::cout << "flag is " << flag << std::endl;
        if (flag == true) {

            break;
        } else {
            quit = true;
            std::cout << "flag is " << flag << std::endl;
            break;
        }


    }


    // While application is running

    while (!quit && !model->quit && model->isPlayerAlive() && !model->checkWinning()) {

        // Get user input
        Input(&quit);
        // If you have time, implement your frame capping code here
        // Otherwise, this is a cheap hack for this lab.
        SDL_Delay(60);
        // Update our scene
        Update();
        // Render using OpenGL
        Render();
        //Update screen of our specified window
    }
    bool gameContinues = false;
    if (!model->isPlayerAlive()) {
        GameOverScreen* gameOverScreen = new GameOverScreen(renderer, (gamePixel * model->getCaveList()[0].size()) + 4 * gamePixel,
                                      (gamePixel * model->getCaveList().size()), window);
        bool gflag = false;
        gameOverScreen->Render(renderer);
        // Wait for the user to press 's' or close the window
        while (!gflag) {

            SDL_Delay(100);
//         To prevent high CPU usage, add a short delay
            gflag = gameOverScreen->Update();
            std::cout << "flag is " << flag << std::endl;
            if (gflag == true) {
                gameContinues = gflag;
                break;
            } else {
                quit = true;
                gameContinues = false;
                //std::cout<<"flag is "<<flag<<std::endl;
                break;
            }


        }

    }
    if (model->checkWinning() && model->isPlayerAlive()) {
        EndWiningScreen* endWiningScreen = new EndWiningScreen(renderer, (gamePixel * model->getCaveList()[0].size()) + 4 * gamePixel,
                                        (gamePixel * model->getCaveList().size()), window);

        // Show the start screen
        endWiningScreen->Render(renderer);
        bool wflag = false;
        // Wait for the user to press 's' or close the window
        while (!wflag) {
            SDL_Delay(100);
            wflag = endWiningScreen->Update();
            if (wflag == true) {
                gameContinues = wflag;
                break;
            } else {
                quit = true;
                gameContinues = false;
                break;
            }
        }
    }

    SDL_StopTextInput();
    return  gameContinues;

}

void Engine::Start() {
    // Report which subsystems are being initialized
    if(mRenderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

    caluclateLocations();

     renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
     window = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetWindow();

     startScreen = new StartScreen(renderer, (gamePixel * model->getCaveList()[0].size()) + 4 * gamePixel, (gamePixel * model->getCaveList().size()),window);


     // TileMap
    GameObject tileMapObject;
    std::cout << model->printMaze() << std::endl;
    TileMapComponent* tileMapComponent = new TileMapComponent( gamePixel,gamePixel,model->getCaveList().size(),model->getCaveList()[0].size(), renderer, model->getCaveList(), this->tilesImg);
    tileMapObject.AddComponent(tileMapComponent);
    m_gameObjects.push_back(tileMapObject);

    // Audio
    AudioComponent* audioComponent = new AudioComponent();
    audioComponent->initMixer();
    std::vector<std::string> sounds;
    sounds.push_back("Arrow");
    sounds.push_back("bgMusic");
    sounds.push_back("coin");
    sounds.push_back("Dice 01");
    sounds.push_back("footsteps");
    sounds.push_back("item-equip");
    sounds.push_back("monsterSound");
    audioComponent->loadSound(sounds);


    // Creating all transform components
    TransformComponent* ttransformComponent = new TransformComponent("treasure");
    TransformComponent* atransformComponent = new TransformComponent("arrow");
    TransformComponent* mtransformComponent = new TransformComponent("monster");
    TransformComponent* ptransformComponent = new TransformComponent("player");
    TransformComponent* dicetransformComponent = new TransformComponent("dice");
    TransformComponent* textTransformComponent = new TransformComponent("text");
    TransformComponent* ssTransformComponent = new TransformComponent("startScreen");
    
    // adding all transform component to controller
    ControllerComponent* controllerComponent = new ControllerComponent(ttransformComponent,atransformComponent,
                                                                       mtransformComponent,ptransformComponent,
                                                                       dicetransformComponent, textTransformComponent,
                                                                       ssTransformComponent,audioComponent, model);


    //End Cave Door
    EndCaveSpriteComponent* endCavesprite= new EndCaveSpriteComponent(gamePixel);
    std::vector<int> vec = model->getEndcave();
    std::cout << "Vector " << vec.at(0)<< vec.at(1) <<std::endl;
    endCavesprite->SetPosition(vec.at(0),vec.at(1));
    endCavesprite->LoadImage(renderer);
    endCave.AddComponent(endCavesprite);
    m_gameObjects.push_back(endCave);




    //Treasure
    TreasureSpriteComponent* tspriteComponent = new TreasureSpriteComponent(ttransformComponent, gamePixel);
    tspriteComponent->SetPosition(treasureCaveID,treasureX,treasureY);
    std::string treasureFile = "treasure1";
    tspriteComponent->LoadImage(treasureFile, renderer);
    treasure.AddComponent(tspriteComponent);
    treasure.AddComponent(ttransformComponent);
    treasure.AddComponent(controllerComponent);
    m_gameObjects.push_back(treasure);


    //Arrow
    ArrowSpriteComponent* aspriteComponent = new ArrowSpriteComponent(atransformComponent, gamePixel);
    aspriteComponent->SetPosition(arrowCaveID,arrowX,arrowY);
    std::string arrowFile = "axe1";
    aspriteComponent->LoadImage(arrowFile, renderer);
    arrow.AddComponent(aspriteComponent);
    arrow.AddComponent(atransformComponent);

    m_gameObjects.push_back(arrow);


    //Monster
    MonsterSpriteComponent* mspriteComponent = new MonsterSpriteComponent(mtransformComponent, gamePixel);

    mspriteComponent->SetPosition(monsterCaveID,monsterX,monsterY);
    mspriteComponent->setType("idle");
    mspriteComponent->LoadImage(this->monsterImg, renderer);
    monsters.AddComponent(mspriteComponent);
    monsters.AddComponent(mtransformComponent);
    monsters.AddComponent(controllerComponent);
    m_gameObjects.push_back(monsters);


    // Player
    SpriteComponent* spriteComponent = new SpriteComponent(ptransformComponent, gamePixel);
    Cave* cave = calculatePlayerPosition();
    ptransformComponent->SetPosition(cave->getRowNo(),cave->getColumnNo());
    spriteComponent->SetPosition(cave->getRowNo(),cave->getColumnNo());
    spriteComponent->setType("idle");
    ptransformComponent->SetAnimType("idle");
    spriteComponent->LoadImage(this->playerImg, renderer);
    character.AddComponent(spriteComponent);
    character.AddComponent(ptransformComponent);
    character.AddComponent(controllerComponent);
    m_gameObjects.push_back(character);

   


    // Dice
    DiceSpriteComponent *dicesprite = new DiceSpriteComponent(dicetransformComponent, gamePixel, model->getBoardRow(), model->getBoardCol());
    dicesprite->SetPosition(gamePixel, model->getCaveList()[0].size());
    dicesprite->setType("stop");
    dicesprite->LoadImage("diceMagenta", renderer);
    dice.AddComponent(dicesprite);
    dice.AddComponent(dicetransformComponent);
    dice.AddComponent(controllerComponent);
    m_gameObjects.push_back(dice);


    // Text
    textComponent = new TextComponent(textTransformComponent, gamePixel);
    textComponent->SetPosition(model->getCaveList().size(), model->getCaveList()[0].size());
    textComponent->LoadFont("Arial", 15, renderer);
    textComponent->setText(model->playerDetails());
    text.AddComponent(textComponent);
    text.AddComponent(textTransformComponent);
    text.AddComponent(controllerComponent);
    m_gameObjects.push_back(text);

//    // Text
//    TextComponent* instructions = new TextComponent(textTransformComponent, gamePixel);
//    instructions->SetPosition(model->getCaveList().size(), model->getCaveList()[0].size());
//    instructions->LoadFont("Arial", 15, renderer);
//
//    instructions->setText(instruct.str());
//    instructionstxt.AddComponent(instructions);
//    instructionstxt.AddComponent(textTransformComponent);
//    m_gameObjects.push_back(instructionstxt);


}

void Engine::Shutdown(){
    // Shut down our Tile Systems
    if(nullptr!=mRenderer){
        delete mRenderer;
    } 

    // Destroy our tilemap
    if(nullptr!=myTileMap){
        delete myTileMap;
    }


}

void Engine::InitializeGraphicsSubSystem(int w, int h, std::string tileImg, std::string playerImg, std::string monsterImg){
    this->tilesImg = tileImg;
    this->playerImg = playerImg;
    this->monsterImg = monsterImg;
    // Setup our Renderer
    mRenderer = new SDLGraphicsEngineRenderer(w,h);
    if(nullptr == mRenderer){
        exit(1); // Terminate program if renderer 
                 // cannot be created.
                 // (Optional) TODO:   Could put an error 
                 //                    messeage, or try to 
                 //                    reinitialize the engine 
                 //                    with a different render
    }
}





Cave* Engine::calculatePlayerPosition(){
    int currentLocation = std::stoi(model->playerLocationDetails().at(1));
    return model->getCave(currentLocation);
}


void Engine::caluclateLocations() {
    std::unordered_map<int,const Vec2D*> resmap;
    std::cout<< "here"<< std::endl;
    std::vector<std::vector <Cave*>> caveList = model->getCaveList();
    for(int i=0; i < caveList.size(); i++) {
        for(int j=0; j< caveList[0].size(); j++){
            Cave* cave = caveList.at(i).at(j);
            if(cave->getMonster() != nullptr){
//                Vec2D* mPos;
                monsterCaveID.push_back(cave->getCaveId());
                monsterX.push_back(cave->getRowNo());
                monsterY.push_back(cave->getColumnNo());

//                mPos->x = caveList.at(i).at(j)->getRowNo();
//                mPos->y = caveList.at(i).at(j)->getColumnNo();
//                resmap.insert(std::make_pair(caveList.at(i).at(j)->getCaveId(),mPos));
            }
            if(model->checkTreasureInCave(cave) == true){
                treasureCaveID.push_back(cave->getCaveId());
                treasureX.push_back(cave->getRowNo());
                treasureY.push_back(cave->getColumnNo());
            }
            if(model->checkArrow(cave) == true){
                arrowCaveID.push_back(cave->getCaveId());
                arrowX.push_back(cave->getRowNo());
                arrowY.push_back(cave->getColumnNo());
            }
        }
    }

}




