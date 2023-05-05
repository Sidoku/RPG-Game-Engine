//
// Created by Sanjana Nalawade on 4/4/23.
//


#include "../../include/GameWorld/Controller.h"
#include <stdexcept>
#include <string>
#include <iostream>


Controller::Controller(GameModel model) : model(model){}

void Controller::start(){

        bool gameRunning = true;
        std::string playerName = "Alice";
        while (!model.checkWinning() && model.isPlayerAlive() && gameRunning) {
            playerDetails(playerName);
            std::cout << "___________________________________\n   Available Paths: \n\n"
                       + model.availablePaths()
                       + "  \n" + "___________________________________" << std::endl;
            int input = menu();

            switch (input) {
                case 1:
                    move();
                    break;
                case 2:
                    pickup();
                    break;
                case 3:
                    shoot();
                    break;
                case 4:
                    gameRunning = false;
                    break;
                case 5:
                    std::cout << "*******CHEAT MODE********" << std::endl;
                    std::cout << "Yellow : Caves with Arrows" << std::endl;
                    std::cout << "Green : Caves with Monster" << std::endl;
                    std::cout << "Purple : Caves with Monster and Arrows" << std::endl;
                    std::cout << model.printMaze() << std::endl;
                    break;
                default:
                    std::cout << "Invalid input please enter again" << std::endl;
                    break;
            }

        }
        if (model.checkWinning() && model.isPlayerAlive()) {
            winning(playerName);
        } else if (!model.isPlayerAlive()) {
            std::cout << "Chomp, chomp, chomp, you are eaten by an Otyugh!\n"
                       << "Better luck next time" << std::endl;
        }
}

void Controller::winning(std::string playerName) {
    std::cout << "___________________________________\n  !!!!!! CONGRATULATIONS "
               + playerName + " !!!!!! "
               + "  \n" + "___________________________________" << std::endl;

    std::cout << playerName + " Successfully Reached the End of the Dungeon" << std::endl;
    std::cout << "Thank you for playing" << std::endl;
    std::cout << "___________________________________\n\n   Player " + playerName
    + " Details \n" + "___________________________________" << std::endl;
    std::cout << "Treasure : " << std::endl;
    CaveJewels j = model.playerTreasureDetails();
    std::cout << "Diamonds : " + std::to_string(j.getJewels("DIAMONDS")) << std::endl;
    std::cout << "Ruby : " + std::to_string(j.getJewels("RUBY")) << std::endl;
    std::cout << "Sapphire : " + std::to_string(j.getJewels("SAPPHIRE")) << std::endl;
    std::cout << "Current Location : " + model.playerLocationDetails()[0] + " "
    + model.playerLocationDetails()[1] << std::endl;
}

void Controller::playerDetails(std::string playerName) {
    std::cout << "___________________________________ \n\n Player " + playerName
                 + " Details \n" + "___________________________________" +  "\n";
    std::cout << "Treasure : " << std::endl;
    CaveJewels j = model.playerTreasureDetails();
    std::cout << "Diamonds : " + std::to_string(j.getJewels("DIAMONDS")) << std::endl;
    std::cout << "Ruby : " + std::to_string(j.getJewels("RUBY")) << std::endl;
    std::cout << "Sapphire : " + std::to_string(j.getJewels("SAPPHIRE")) << std::endl;
    std::cout << "Arrows Count : " + std::to_string(model.playerArrowDetails()) << std::endl;
    std::cout << "Current Location : " + model.playerLocationDetails()[0] + " "
                 + model.playerLocationDetails()[1] + "\n";
    std::cout << model.smell() + "\n";
}

int Controller::menu() {
        int val;
        std::cout << "___________________________________\n  Type Following Number: \n\n"
                   << "1.Move\n2.Pickup\n3.Shoot\n4.Quit"
                   << "  \n" << "___________________________________" << std::endl;
        std::cin >> val;
        return val;
}

void Controller::move(){
    char inmove = '0';
    std::string move = "";
    bool isValidMove = false;
    std::cout << "___________________________________\n   Enter Following Character: \n\n"
               << "             W: North \n                 ^ \n A: West       <   >       D: East"
               << "  \n                 v \n              S: South"
               << "  \n" << "___________________________________" << std::endl;
    while (!isValidMove) {
        std::cin >> inmove;
        switch (inmove) {
            case 'W' :
            case 'w' :
                move = "NORTH";
                break;
            case 'S':
            case 's':
                move = "SOUTH";
                break;
            case 'D':
            case 'd':
                move = "EAST";
                break;
            case 'A':
            case 'a':
                move = "WEST";
                break;
        }
        if (!model.checkValidMove(move)) {
            std::cout << "Invalid Move , Please Enter Move from Available Path" << std::endl;
        } else {
            isValidMove = true;
        }
    }
    model.moveToPosition(move);
}

void Controller::pickup() {
    bool flag = false;
    if (model.checkArrow(model.currentCave)) {
         std::cout << "****Arrow Available in Cave*****" << std::endl;
         std::cout << "Type Y to pick the Arrow or type anything else to continue without picking" << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "y" || input == "Y") {
            model.pickupArrow();
        }
    } else {
         std::cout << " No Arrows Available !!!" << std::endl;
    }
    while (model.checkTreasureInCave(model.currentCave)) {
        flag = true;
         std::cout << " Available Treasure : " + model.availableTreasure() << std::endl;
         std::cout << "****Treasure Available in Cave*****" << std::endl;
         std::cout << "Type Y to pick the Treasure or type anything else to continue without picking" << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "y" || input == "Y") {
             std::cout << " Available Treasure : " + model.availableTreasure() << std::endl;
             std::cout << "Type Following Number:" << std::endl;
             std::cout << "1.Diamonds\n2.Ruby\n3.Sapphire\n" << std::endl;
            int i;
            std::cin >> i;
            switch (i) {
                case 1:
                    model.pickupTreasure("DIAMONDS");
                    break;
                case 2:
                    model.pickupTreasure("RUBY");
                    break;
                case 3:
                    model.pickupTreasure("SAPPHIRE");
                    break;
                default:
                     std::cout << "Invalid Input Enter Again" << std::endl;
                    break;
            }
            if (model.checkTreasureInCave(model.currentCave)) {
                 std::cout << "Do you want to pickup More Treasure ?" << std::endl;
            }
        } else {
            break;
        }
    }
    if (!model.checkTreasureInCave(model.currentCave) && !flag) {
         std::cout << " Treasure Not Available !!!" << std::endl;
    }
}

void Controller::shoot() {
    bool isValidMove = false;
    std::string move = "";
    char inmove = '0';
    int count;
    int caveCount = 0;
    if (model.checkPlayerArrow()) {
        std::cout << "Number Caves to Shoot?" << std::endl;
        std::cin >> count;
        caveCount = count;
        std::cout << "___________________________________\n   Enter Following Character: \n\n"
                   << "             W: North \n                 ^ \n A: West       <   >       D: East"
                   << "  \n                 v \n              S: South"
                   << "  \n" << "___________________________________" << std::endl;

        std::cin >> inmove;
        switch (inmove) {
            case 'W' :
            case 'w' :
                move = "NORTH";
                break;
            case 'S':
            case 's':
                move = "SOUTH";
                break;
            case 'D':
            case 'd':
                move = "EAST";
                break;
            case 'A':
            case 'a':
                move = "WEST";
                break;
        }
         std::cout << model.shoot(move, caveCount) << std::endl;

    } else {
         std::cout << "You are out of arrows, explore to find more\n" << std::endl;
    }

}