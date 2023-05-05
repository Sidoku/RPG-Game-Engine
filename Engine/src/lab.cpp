// Support Code written by Michael D. Shah
// Last Updated: 2/19/21
// Please do not redistribute without asking permission.


#include "../include/Engine.hpp" // The main engine
#include "../include/IGraphicsEngineRenderer.hpp" // The renderering engine
#include "../include/GameWorld/Random.h"
#include "../include/GameWorld/GameModel.h"
#include <iostream>
#include <string>
#include "../include/GameWorld/Controller.h"
#include <chrono>
#include <thread>

int row = 7;
int col = 8;
bool wrap = true;
int treasure = 30;
int monster = 12;
std::string name = "Sanjana";
int interconnectivity = 2;
int pix = 100;
std::string tileTheme = "Theme1";
std::string playerChar = "Knight";
std::string monsterChar = "ORK2";

//int row = 6;
//int col = 6;
//bool wrap = true;
//int treasure = 30;
//int monster = 12;
//std::string name = "Sanjana";
//int interconnectivity = 3;
//int pix = 100;

int main(int argc, char** argv){

    bool gamePlay = true;

    while (gamePlay) {


        std::cout << "Row : " << row
                  << " Col : " << col
                  << " interconnectivity : " << interconnectivity
                  << " wrap : " << wrap
                  << " treasure: " << treasure
                  << " monster : " << monster
                  << " name: " << name << std::endl;


        GameModel model = GameModel(row,  col, interconnectivity, wrap, treasure,  monster, name,pix);
        //   Controller controller = Controller(model);
        //   std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << model.printMaze() << std::endl;
        //controller.start();

// Commnting below code for SDL
        // Create an instance of an object for our engine
        Engine engine(&model);
        // Initialize the Engine Subsystems
        engine.InitializeGraphicsSubSystem((row*pix) + 4 * pix, (col*pix),tileTheme,playerChar, monsterChar);

        // Once all subsystems have been initialized
        // Start the engine
        engine.Start();
        // Run our program forever
        gamePlay = engine.MainGameLoop();
        // Explicitly call Shutdown to terminate our engine
        engine.Shutdown();
        // When our program ends, it will exit scope,
        // the destructor will then be called
        // and clean up the program.
    }

//    std::cout << "Enter player name : " << std::endl;
//    std::cin >> name;


	return 0;

}




