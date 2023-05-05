//
// Created by Sanjana Nalawade on 4/4/23.
//


#include "../../include/GameWorld/GameModel.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include "../../include/GameWorld/Dungeon.h"
#include "../../include/GameWorld/enums/CaveJewels.h"
#include <algorithm>

#include <iostream>

GameModel::GameModel(int ycoordinate, int xcoordinate, int interconnectivity, bool isWrapping,
            int treasurePercentage, int monsterCount, std::string playerName, int pix)
 {
    //std::cout << "Monster Count " << monsterCount << "Expected to be less than " << xcoordinate * ycoordinate - 1 <<std::endl;
        if (monsterCount <= 0 || monsterCount >= (xcoordinate * ycoordinate - 1)) {
            throw std::invalid_argument("Invalid Count of Monster ");
        }
        //Throws exception if any coordinate is less than or equal to 0
        if (xcoordinate <= 0 || ycoordinate <= 0) {
            throw std::invalid_argument("Coordinates of Maze Grid Cannot be negative");
        }
        //Throws exception if the grid contains less than 10 spots
        if (xcoordinate * ycoordinate < 10) {
            throw std::invalid_argument("Please Provide larger values for coordinates");
        }
        //Throws exception if the random object is nullptr
        if (&random == nullptr) {
            throw std::invalid_argument("Illegal Random");
        }
        //throws exception if the treasure percentage is less than or equal to zero.
        if (treasurePercentage <= 0 || treasurePercentage > 100) {
            throw std::invalid_argument("Invalid Treasure Percentage");
        }
        //Throws exception if the interconnectivity is less than or equal to 0.
        if (interconnectivity < 0) {
            throw std::invalid_argument("Interconnectivity is too low");
        }
        //Throws exception if player Name is nullptr or empty string
        if (playerName == " " || playerName == "" ) {
            throw std::invalid_argument("Invalid Player Name");
        }
         dungeon = new Dungeon(xcoordinate,
                               ycoordinate,
                               interconnectivity,
                               treasurePercentage,
                               isWrapping,
                               monsterCount,
                               &random);
        this->currentCave = dungeon->getStartCave();
        player = new Player(playerName, currentCave->getCaveId());
        visitedCave = std::set<int> () ;
        visitedCave.insert(currentCave->getCaveId());
        m_pix = pix;
        boardRow = xcoordinate;
        boardCol = ycoordinate;

        


}
int GameModel::getBoardRow() {
    return boardRow;
}

int GameModel::getBoardCol() {
    return boardCol;
}
   

int GameModel::getRandomValue(int min, int max) {
    return random.getRandomNumber(min, max);
}

std::string GameModel::printMaze() {
    return dungeon->printDungeon(currentCave);
}


bool GameModel::checkWinning() {
    if (!isPlayerAlive()) {
        return false;
    }
    return currentCave->getCaveId() == dungeon->getEndCave()->getCaveId();
}

std::vector<int> GameModel::getEndcave() {
    std::vector<int> endcord;
    endcord.push_back(dungeon->getEndCave()->getRowNo());
    endcord.push_back(dungeon->getEndCave()->getColumnNo());
    return endcord;
}
CaveJewels GameModel::playerTreasureDetails() {
    CaveJewels treasureDetailsPlayer;
    treasureDetailsPlayer.setJewels("DIAMONDS",  player->getTreasureCount("DIAMONDS"));
    treasureDetailsPlayer.setJewels("SAPPHIRE",  player->getTreasureCount("SAPPHIRE"));
    treasureDetailsPlayer.setJewels("RUBY",  player->getTreasureCount("RUBY"));
    return treasureDetailsPlayer;
}


std::vector<std::string> GameModel::playerLocationDetails() {
    std::vector<std::string> playerLocation =  std::vector<std::string> (2);
    Cave* cave = dungeon->getCave(player->getPlayerLocation());
    if (cave->isTunnel()) {
        playerLocation[0] = "Tunnel";
    } else {
        playerLocation[0] = "Cave";
    }
    playerLocation[1] = std::to_string(cave->getCaveId());
    return playerLocation;

}


std::string GameModel::availablePaths() {
    std::unordered_map<std::string, int>  direction = currentCave->getDirection();
    std::ostringstream oss;
    for (const auto& d : direction) {
        if (d.second > 0) {
            oss << d.first << "  Cave: " << d.second << "\n";
        }
    }
    return oss.str();
}


bool GameModel::checkValidMove(std::string move) {
    if (move == "") {
        throw std::invalid_argument("Invalid Move");
    }

    return currentCave->getDirection()[move] != 0;
}


void GameModel::moveToPosition(std::string move)  {
    if (move == "" ) {
        throw std::invalid_argument("Invalid Move");
    }
    int nextCaveId = this->currentCave->getDirection().find(move)->second;
    this->currentCave = dungeon->getCave(nextCaveId);
    player->setPlayerLocation(nextCaveId);
    visitedCave.insert(currentCave->getCaveId());
}


std::string GameModel::availableTreasure() {
    std::stringstream ss;
    ss << "{DIAMONDS=" << currentCave->getCaveTreasure("DIAMONDS");
    ss << ", RUBY=" << currentCave->getCaveTreasure("RUBY");
    ss << ", SAPPHIRE=" << currentCave->getCaveTreasure("SAPPHIRE") << "}";
    return ss.str();
}



std::vector<int> GameModel::mazeDetails() {
    std::vector<int> maze;
    maze.push_back(dungeon->getStartCave()->getCaveId());
    maze.push_back(dungeon->getEndCave()->getCaveId());
    return maze;
}



bool GameModel::checkTreasureInCave(Cave* cave) {
    bool treasureFlag = false;
    std::string myjewels[3] = {"DIAMONDS", "RUBY", "SAPPHIRE"};
    for (const auto& caveJewels : myjewels) {
        if (cave->getCaveTreasure(caveJewels) != 0) {
            treasureFlag = true;
            /*return treasureFlag;*/
        }
    }
    return treasureFlag;
}


void GameModel::pickupTreasure(std::string caveJewels) {
    if (currentCave->getCaveTreasure(caveJewels) > 0) {
        player->setTreasureCount(caveJewels, currentCave->getCaveTreasure(caveJewels));
        dungeon->updateTreasure(currentCave, caveJewels);
        currentCave->setCaveTreasure(caveJewels, 0);
    }
}



bool GameModel::checkArrow(Cave* cave) {
    return cave->isArrow();
}


void GameModel::pickupArrow() {
    if (checkArrow(this->currentCave)) {
        player->updateArrowCount(true);
        dungeon->updateArrow(currentCave);
        currentCave->setArrow(false);
    }
}


std::string GameModel::shoot(std::string move, int count) {
    std::string path_aaray[4] = {"NORTH", "SOUTH", "EAST", "WEST"};
    if (!checkValidMove(move)) {
        player->updateArrowCount(false);
        return "You shoot an arrow into the darkness";
    }
    if (count <= 0) {
        throw std::invalid_argument("Invalid count");
    }
    player->updateArrowCount(false);
    std::vector<int> visited = std::vector<int>();
    int nextCaveId = currentCave->getCaveId();

    std::stringstream result;
    visited.push_back(nextCaveId);
    while (count > 0) {
         nextCaveId = dungeon->getCave(nextCaveId)->getDirection().find(move)->second;
            if (nextCaveId != 0) {
                Cave* cave = dungeon->getCave(nextCaveId);

                    for (const auto& d : path_aaray) {
                        auto dirIt = cave->getDirection().find(d);
                        if (dirIt != cave->getDirection().end() && dirIt->second > 0
                            && std::find(visited.begin(), visited.end(), dirIt->second) == visited.end()) {
                            move = d;
                        }
                    }

                    count--;

                visited.push_back(nextCaveId);
            } else {
                result << "You shoot an arrow into the darkness";
                return result.str();
            }

    }
    if (dungeon->getCave(nextCaveId)->getMonster() != nullptr) {
        if (dungeon->getCave(nextCaveId)->getMonster()->getHealth() == 1) {
            dungeon->updateMonsterHealth(nextCaveId);
            dungeon->slayMonster(nextCaveId);
        } else {
            dungeon->updateMonsterHealth(nextCaveId);
        }
        result << "You hear a great howl in the distance !!!";
    } else {
        result << "You shoot an arrow into the darkness";
    }
    return result.str();
}



std::string GameModel::smell() {

    return helperSmell(helperList());
}


bool GameModel::isPlayerAlive() {
    if (currentCave->getMonster() != nullptr) {
        if (currentCave->getMonster()->getHealth() == 2) {
            return false;
        } else {
            int chancceOfDying = random.getRandomNumber(0, 2);
            return chancceOfDying == 1;
        }
    }
    return true;
}


bool GameModel::checkPlayerArrow() {
    return player->getArrowCount() > 0;
}


int GameModel::playerArrowDetails() {
    return player->getArrowCount();
}

std::string GameModel::helperSmell(std::vector<std::vector<int> > helperList) {
    int monsterCount = 0;
    std::stringstream result;
    std::vector<int> visited;
    for (auto caveId : helperList[0]) {
        if (std::find(visited.begin(), visited.end(), caveId) == visited.end()
            && dungeon->getCave(caveId)->getMonster() != nullptr) {
            result << "You smell something \n more pungent nearby ";
            return result.str();
        }
        visited.push_back(caveId);
    }
    for (auto caveId : helperList[1]) {
        if (std::find(visited.begin(), visited.end(), caveId) == visited.end()
            && dungeon->getCave(caveId)->getMonster() != nullptr) {
            monsterCount++;
        }
        visited.push_back(caveId);
    }

    if (monsterCount >= 2) {
        result << "You smell something \n more pungent nearby ";
    } else if (monsterCount == 1) {
        result << "You smell something \n more pungent nearby ";
    } else {
        result << " ";
    }
    return result.str();
}



std::vector<std::vector<int> > GameModel::helperList() {
    std::string path_aaray[4] = {"NORTH", "SOUTH", "EAST", "WEST"};
    std::vector<std::vector<int> > caveList;
    std::vector<int> neighbour1;
    std::vector<int> neighbour2;
    int caveId = currentCave->getCaveId();
    for (const auto& paths : path_aaray) {
        if (dungeon->getCave(caveId)->getDirection().find(paths)->second > 0) {
            int newCaveId = dungeon->getCave(caveId)->getDirection().find(paths)->second;
            neighbour1.push_back(newCaveId);
            for (const auto& paths1 : path_aaray){
                if (dungeon->getCave(newCaveId)->getDirection().find(paths1)->second > 0) {
                    neighbour2.push_back(dungeon->getCave(newCaveId)->getDirection().find(paths1)->second);
                }
            }
        }
    }
    caveList.push_back(neighbour1);
    caveList.push_back(neighbour2);
    return caveList;
}



std::vector<std::vector<Cave* > > GameModel::getCaveList() {
    return dungeon->getCaveList();
}

std::string GameModel::getPlayerName() {
    return player->getPlayerName();
}

std::set<int> GameModel::getVisitedCave() {
    return visitedCave;
}



Cave* GameModel::getCave(int caveId) {
    std::vector<std::vector<Cave* > > caveList = getCaveList();
    for(int i=0; i<caveList.size(); i++){
        for (int j=0; j< caveList.at(0).size(); j++){
            if(caveList.at(i).at(j)->getCaveId() == caveId){
                return caveList.at(i).at(j);
            }
        }
    }

    throw std::runtime_error("No cave found");
}

std::unordered_map<int,int> GameModel::getCaveWithTreasure(){
    std::unordered_map<int, int> res;
    std::vector<std::vector<Cave* > > caveList = getCaveList();
    for(int i=0; i<caveList.size(); i++){
        for (int j=0; j< caveList.at(0).size(); j++){
            Cave* cave = caveList.at(i).at(j);
            //if()
            if(checkTreasureInCave(cave) == true){
                res.insert(std::make_pair(cave->getRowNo(),cave->getColumnNo()));
            }
        }
    }
}

int GameModel::getPix(){
    return m_pix;

}

void GameModel::setPlayerdiceRoll(int val) {
    this->player->setDiceRoll(val);
}
int GameModel::getPlayerdiceRoll(){
    return this->player->getDiceRoll();
}


std::string GameModel::playerDetails() {
    std::stringstream details;
   details << "___________ \n Player : " + player->getPlayerName() + "\n___________  \n";
   details << "Treasure : " << "\n";
    CaveJewels j = playerTreasureDetails();
   details << "Diamonds : " + std::to_string(j.getJewels("DIAMONDS")) <<"\n";
   details << "Ruby : " + std::to_string(j.getJewels("RUBY")) <<"\n";
   details << "Sapphire : " + std::to_string(j.getJewels("SAPPHIRE")) <<"\n___________  \n";
   details << "Axe Count : " + std::to_string(playerArrowDetails()) <<"\n___________  \n";
//   details << "Current Location : " + playerLocationDetails()[0] + " "
//                 + playerLocationDetails()[1] + "\n";
   details << "Smell : \n" + smell() + "\n___________  \n";
   details << "Moves Remaining : \n" + std::to_string(player->getDiceRoll())<< "\n";
   return details.str();
}