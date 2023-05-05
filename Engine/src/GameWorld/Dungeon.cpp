//
// Created by Sanjana Nalawade on 4/4/23.
//

#include "../../include/GameWorld/Dungeon.h"
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <initializer_list>
#include <iostream>

Dungeon::Dungeon(int xcoordinate, int ycoordinate, int interconnectivity,
                 int treasurePercentage, bool isWrapping1, int monsterCount,
                 Random* random) :
               xcoordinate(xcoordinate), ycoordinate(ycoordinate),
               interconnectivity(interconnectivity), treasurePercentage(treasurePercentage),
               isWrapping(isWrapping1), monsterCount(monsterCount), random(*random) {

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
        //throws exception if the treasure percentage is less than or equal to zero.
        if (treasurePercentage <= 0 || treasurePercentage > 100) {
            throw std::invalid_argument("Invalid Treasure Percentage");
        }
        //Throws exception if the random object is null
        if (random == nullptr) {
            throw std::invalid_argument("Illegal Random");
        }
        //Throws exception if the interconnectivity is less than or equal to 0.
        if (interconnectivity < 0) {
            throw std::invalid_argument("Interconnectivity is too low");
        }
        Cave startCave();
        Cave endCave();
        flagStartEndAssigned = false;
        //Calls a private method for initializing dungeon
        initializeDungeon();
        //std::cout << " Dungeons Created "  <<std::endl;

}

void Dungeon::initializeDungeon() {
    //std::cout << "In initializeDungeon" <<std::endl;

    initializeCave();
    createPossiblePathList();
    createLinks(createSets());
    updateTunnel();
    selectStartEndCave();
    initializeTreasureArrow(treasurePercentage, "TREASURE");
    initializeTreasureArrow(treasurePercentage, "ARROW");
    initializeMonsters();


}


void Dungeon::initializeMonsters() {
    //std::cout << "In initilizing monster" <<std::endl;
    int countOfMonsters = 1;
    Monster* endMonster = new Otyugh(1);
    std::vector<int> cavesWithMonsters;
    endCave->setMonster(endMonster);
    monsterList.push_back(endMonster);
    countOfMonsters++;
    cavesWithMonsters.push_back(endCave->getCaveId());
    while (cavesWithMonsters.size() != monsterCount) {
        int randomNumber = random.getRandomNumber(1, (xcoordinate * ycoordinate - 1));
        auto condition = std::find(cavesWithMonsters.begin(), cavesWithMonsters.end(), randomNumber);
        if (condition == cavesWithMonsters.end()) {
            for (int i = 0; i < xcoordinate; i++) {
                for (int j = 0; j < ycoordinate; j++) {
                    if (caveList.at(i).at(j)->getCaveId() == randomNumber) {
                        if (!caveList.at(i).at(j)->isTunnel()
                                && caveList.at(i).at(j)->getCaveId() != startCave->getCaveId()) {
                            Monster* m = new Otyugh(countOfMonsters);
                            caveList.at(i).at(j)->setMonster(m);
                            monsterList.push_back(m);
                            cavesWithMonsters.push_back(caveList.at(i).at(j)->getCaveId());
                            countOfMonsters++;
                            std::cout << "Monster Cave : " << caveList.at(i).at(j)->getCaveId() << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void Dungeon::initializeTreasureArrow(int elementPercent, std::string elementType) {
    //std::cout << "In treasure arrow initilzation" <<std::endl;
    if (elementPercent >= 0) {
        int treasureNumber = std::round((treasurePercentage * xcoordinate * ycoordinate) / 100);
        std::vector<int> elementIndex;
        while (elementIndex.size() != treasureNumber) {
            //std::cout << elementIndex.size() << std::endl;
            int randomNumber = random.getRandomNumber(1, (xcoordinate * ycoordinate));
            auto condition = std::find(elementIndex.begin(), elementIndex.end(), randomNumber);
            if (condition == elementIndex.end()) {
                for (int i = 0; i < xcoordinate; i++) {
                    for (int j = 0; j < ycoordinate; j++) {
                        if (caveList.at(i).at(j)->getCaveId() == randomNumber) {
                            if (elementType.compare("TREASURE") && !caveList.at(i)
                                    .at(j)->isTunnel()) {
                                caveList.at(i).at(j)->setCaveTreasure("RUBY",
                                                                       random.getRandomNumber(0, 3) * 100);
                                caveList.at(i).at(j)->setCaveTreasure("SAPPHIRE",
                                                                       random.getRandomNumber(0, 3) * 100);
                                if (caveList.at(i).at(j)->getCaveTreasure("RUBY") == 0
                                    && caveList.at(i).at(j)->getCaveTreasure("SAPPHIRE") == 0) {
                                    caveList.at(i).at(j)->setCaveTreasure("DIAMONDS",
                                                                           random.getRandomNumber(1, 3) * 100);
                                } else {
                                    caveList.at(i).at(j)->setCaveTreasure("DIAMONDS",
                                                                           random.getRandomNumber(0, 3) * 100);
                                }
                                elementIndex.push_back(randomNumber);
                            } else if (elementType.compare("ARROW")) {
                                caveList.at(i).at(j)->setArrow(true);
                                elementIndex.push_back(randomNumber);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Dungeon::updateTunnel() {
    std::string path_aaray[4] = {"NORTH", "SOUTH", "EAST", "WEST"};
    //std::cout << "ee" <<std::endl;
    for (int i = 0; i < xcoordinate; i++) {
        for (int j = 0; j < ycoordinate; j++) {
            int count = 0;
            for (const auto& d : path_aaray) {
                if (caveList.at(i).at(j)->getDirection().at(d) != 0) {
                    count++;
                }
            }

            if (count == 2) {
                caveList.at(i).at(j)->setTunnel(true);
            }
        }
    }
}

void Dungeon::createLinks(std::vector<std::unordered_set<int> > hashSetList) {
    if (hashSetList.size() == 0) {
        throw std::invalid_argument("Hashset is empty");
    }
    while (possiblePath.size() != 0) {
        int randomNumber = random.getRandomNumber(0, possiblePath.size() - 1);
        std::vector<Cave*> possiblePath1 = possiblePath.at(randomNumber);

        std::unordered_set<int> set1 = getSets(hashSetList, possiblePath1[0]->getCaveId());

        std::unordered_set<int> set2 = getSets(hashSetList, possiblePath1[1]->getCaveId());
        if (set1 == set2) {
            leftOverList.push_back(possiblePath1);

        } else {
            std::unordered_set<int> mergeSet = std::unordered_set<int> ();
            mergeSet.insert(set1.begin(), set1.end());
            mergeSet.insert(set2.begin(), set2.end());

            updateCaveDirection(possiblePath1);
            hashSetList.push_back(mergeSet);

            auto it1 = std::find(hashSetList.begin(), hashSetList.end(), set1);
            if (it1 != hashSetList.end()) {
                hashSetList.erase(it1);
            }

            auto it2 = std::find(hashSetList.begin(), hashSetList.end(), set2);
            if (it2 != hashSetList.end()) {
                hashSetList.erase(it2);
            }
        }

        // Find the iterator pointing to possiblePath1 in possiblePath
        auto it = std::find(possiblePath.begin(), possiblePath.end(), possiblePath1);

        if (it != possiblePath.end()) {
            possiblePath.erase(it);
        }
    }

    connectLeftover();
}

void Dungeon::connectLeftover() {
    int interconnectivityCount = interconnectivity;
    if (leftOverList.size() > interconnectivity) {
        while (interconnectivityCount != 0) {
            int randomNumber = random.getRandomNumber(0, leftOverList.size() - 1);
            std::vector<Cave*> possiblePath2 = leftOverList.at(randomNumber);
            updateCaveDirection(possiblePath2);
            /*   adjacencyMatrix[possiblePath2[0]][possiblePath2[1]]=1;*/
            leftOverList.erase(leftOverList.begin() + randomNumber);
            interconnectivityCount--;

        }
    }
}

std::unordered_set<int> Dungeon::getSets(std::vector<std::unordered_set<int> >& hashSetList, int caveId) {
    //std::cout << std::to_string(caveId) << "Cave Id:" <<std::endl;
    if (hashSetList.empty()) {
        throw std::invalid_argument("Hash set List is empty");
    }
    if (caveId <= 0 || caveId > xcoordinate * ycoordinate) {
        throw std::invalid_argument("get sets :: Invalid Cave Id" );
    }
    for (std::unordered_set<int>& set : hashSetList) {
        if (set.find(caveId) != set.end()) {
            return set;
        }
    }
    throw std::invalid_argument("Invalid Cave Id");
}


void Dungeon::updateCaveDirection(std::vector<Cave*> possiblePath1) {
    //std::cout << "Inside updated Cave direction" << std::endl;
    if (possiblePath1.size() <= 0) {
        throw std::invalid_argument("Invalid Possible Paths");
    }
    int row1 = possiblePath1[0]->getRowNo();
    int col1 = possiblePath1[0]->getColumnNo();
    int row2 = possiblePath1[1]->getRowNo();
    int col2 = possiblePath1[1]->getColumnNo();
    if (row1 == row2 - 1) {
        possiblePath1[0]->setDirection("SOUTH", possiblePath1[1]->getCaveId());
        possiblePath1[1]->setDirection("NORTH", possiblePath1[0]->getCaveId());
    }
    if (col1 == col2 - 1) {
        possiblePath1[0]->setDirection("EAST", possiblePath1[1]->getCaveId());
        possiblePath1[1]->setDirection("WEST", possiblePath1[0]->getCaveId());
    }
    if (isWrapping) {
        if (col1 == 0 && col2 == ycoordinate - 1 && row1 == row2) {
            possiblePath1[0]->setDirection("WEST", possiblePath1[1]->getCaveId());
            possiblePath1[1]->setDirection("EAST", possiblePath1[0]->getCaveId());
        }
        if (row1 == 0 && row2 == xcoordinate - 1 && col1 == col2) {
            possiblePath1[0]->setDirection("NORTH", possiblePath1[1]->getCaveId());
            possiblePath1[1]->setDirection("SOUTH", possiblePath1[0]->getCaveId());
        }
    }

    //std::cout << "Paths:______" <<std::endl;
    //std::cout << possiblePath1[0]->getDirection()["NORTH"] << std::endl;
    //std::cout << possiblePath1[0]->getDirection()["SOUTH"] << std::endl;
    //std::cout << possiblePath1[0]->getDirection()["EAST"] << std::endl;
    //std::cout << possiblePath1[0]->getDirection()["WEST"] << std::endl;
    //std::cout << possiblePath1[1]->getDirection()["NORTH"] << std::endl;
    //std::cout << possiblePath1[1]->getDirection()["SOUTH"] << std::endl;
    //std::cout << possiblePath1[1]->getDirection()["EAST"] << std::endl;
    //std::cout << possiblePath1[1]->getDirection()["WEST"] << std::endl;


}

std::vector<std::unordered_set<int> > Dungeon::createSets() {
    std::vector<std::unordered_set<int> > hashSetList;
    for (int i = 0; i < xcoordinate; i++) {
        for (int j = 0; j < ycoordinate; j++) {
            std::unordered_set<int> hs;
            hs.insert(caveList.at(i).at(j)->getCaveId());
            hashSetList.push_back(hs);
        }
    }

//    for(std::unordered_set<int> set : hashSetList){
//        for(int a : set){
//            //std::cout << se
//        }
//    }
    return hashSetList;
}

void Dungeon::createPossiblePathList() {

    //std::cout << "inside create possible path" << std::endl;
    for (int i = 0; i <= xcoordinate - 1; i++) {
        for (int j = 0; j <= ycoordinate - 1; j++) {
            if (i != xcoordinate - 1 && j != ycoordinate) {
                if (j != ycoordinate - 1) {
                    std::vector<Cave*> c1 ;
                    c1.push_back(caveList.at(i).at(j));
                    c1.push_back(caveList.at(i).at(j + 1));
                    possiblePath.push_back(c1);
                }
                if (i != xcoordinate - 1) {
                    std::vector<Cave*> c2 ;
                    c2.push_back(caveList.at(i).at(j));
                    c2.push_back(caveList.at(i + 1).at(j));
                    possiblePath.push_back(c2);
                }
            }
        }
    }
    if(isWrapping) {
        for (int i = 0; i < xcoordinate - 1; i++) {
            std::vector<Cave*> c3 ;
            c3.push_back(caveList.at(i).at(0));
            c3.push_back(caveList.at(i).at(ycoordinate-1));
            possiblePath.push_back(c3);
        }
        for (int i = 0; i < ycoordinate - 1; i++) {
            std::vector<Cave*> c4 ;
            c4.push_back(caveList.at(0).at(i));
            c4.push_back(caveList.at(xcoordinate-1).at(i));
            possiblePath.push_back(c4);
        }
    }
    //std::cout << "Possible path size" << std::to_string(possiblePath.size()) << std::endl;
//    for (const std::vector<Cave*> row : possiblePath) {
//        for (const Cave* col : row) {
//            //std::cout << col->caveId <<" ";
//        }
//        //std::cout << std::endl;
//    }

}

void Dungeon::initializeCave() {
    //std::cout << "In initializeCave"  <<std::endl;
    int caveId = 1;
    for (int i = 0; i < xcoordinate; i++) {
        std::vector<Cave*> caveRow;
        for (int j = 0; j < ycoordinate; j++) {
            Cave* cave =  new Cave(caveId, i, j);
            caveRow.push_back(cave);
            caveId++;
        }
        caveList.push_back(caveRow);
    }
}


std::vector<std::vector<Cave*> > Dungeon::getCaveList() {
//    std::vector<std::vector<Cave*> > caveListCopy;
//    for (int i = 0; i < xcoordinate; i++) {
//        std::vector<Cave*> rowCaves;
//        for (int j = 0; j < ycoordinate; j++) {
//            Cave cave =  Cave(*caveList.at(i).at(j));
//            rowCaves.push_back(&cave);
//        }
//        caveListCopy.push_back(rowCaves);
//    }
    return caveList;
}

Cave* Dungeon::getStartCave() {
    return this->startCave;
}

Cave* Dungeon::getEndCave() {
    return this->endCave;
}

Cave* Dungeon::getCave(int nextCaveId){
        if (nextCaveId < 0) {
            throw std::invalid_argument("Invalid Cave Id");
        }
        for (int i = 0; i < xcoordinate; i++) {
            for (int j = 0; j < ycoordinate; j++) {
                if (caveList.at(i).at(j)->getCaveId() == nextCaveId) {
                    return caveList.at(i).at(j);
                }
            }
        }
        throw std::runtime_error("Invalid Cave Id");
}

void Dungeon::updateTreasure(Cave* cave, std::string caveJewels) {
        if (&cave == nullptr) {
            throw std::invalid_argument("Cave Object is null");
        }
        if (&caveJewels == nullptr) {
            throw std::invalid_argument("Invalid treasure");
        }
        Cave* caveObj = caveList.at(cave->getRowNo()).at(cave->getColumnNo());
        caveObj->setCaveTreasure(caveJewels, 0);

}

void Dungeon::updateArrow(Cave* cave) {
        if (&cave == nullptr) {
            throw std::invalid_argument("Cave Object is null");
        }
        caveList.at(cave->getRowNo()).at(cave->getColumnNo())->setArrow(false);
}

void Dungeon::slayMonster(int nextCaveId) {
        if (nextCaveId <= 0) {
            throw std::invalid_argument("Invalid Cave Id");
        }
        for (int i = 0; i < xcoordinate; i++) {
            for (int j = 0; j < ycoordinate; j++) {
                if (caveList.at(i).at(j)->getCaveId() == nextCaveId) {
                    caveList.at(i).at(j)->setMonster(nullptr);
                }
            }
        }

}

void Dungeon::selectStartEndCave() {
    //std::cout << "In startendcave selection" <<std::endl;
    while (!flagStartEndAssigned) {
        startEndPath.clear();
        Cave* tempStartCave = getCaveObject();
        Cave* tempEndCave = getCaveObject();
        checkDistance(tempStartCave, tempEndCave);
        std::vector<int> listSize;
        //std::cout<< "start end path size" << std::to_string(startEndPath.size()) << std::endl;
        for (std::vector<int> list : startEndPath) {
            listSize.push_back(list.size());
        }
        //std::cout<< "List size" << std::to_string(listSize.size()) << std::endl;

        for(auto &d : listSize){
            //std::cout<< "List 1" << std::to_string(d) << std::endl;
        }
        //std::cout << "before min" <<std::endl;
        int min = *std::min_element(listSize.begin(), listSize.end());
        //std::cout << "after min update" <<std::endl;
        if (min >= 6) {
            this->startCave = tempStartCave;
            this->endCave = tempEndCave;
            flagStartEndAssigned = true;
        }
    }

}

Cave* Dungeon::getCaveObject() {
    //std::cout << "In getCave object" <<std::endl;
    bool caveFlag = false;
    while (!caveFlag) {
        int randomXnumber = random.getRandomNumber(1, (xcoordinate) - 1);
        int randomYnumber = random.getRandomNumber(1, (ycoordinate) - 1);
        Cave* cave1 = caveList.at(randomXnumber).at(randomYnumber);
        if (!cave1->isTunnel()) {
            return cave1;
        }
    }
    throw std::runtime_error("Valid cave could not be found");
}

void Dungeon::checkDistance(Cave* tempStartCave, Cave* tempEndCave) {
    //std::cout << "In check distance" <<std::endl;
    //std::cout << "Temp cave details" << std::endl;

    //std::cout << tempEndCave->getDirection()["NORTH"] << std::endl;
    //std::cout << tempEndCave->getDirection()["SOUTH"] << std::endl;
    //std::cout << tempEndCave->getDirection()["EAST"] << std::endl;
    //std::cout << tempEndCave->getDirection()["WEST"] << std::endl;
    //std::cout << tempStartCave->getDirection()["NORTH"] << std::endl;
    //std::cout << tempStartCave->getDirection()["SOUTH"] << std::endl;
    //std::cout << tempStartCave->getDirection()["EAST"] << std::endl;
    //std::cout << tempStartCave->getDirection()["WEST"] << std::endl;


    if (&tempStartCave == nullptr || &tempEndCave == nullptr) {
        throw std::invalid_argument("Cave Objects are empty");
    }
    std::vector<std::vector<int> > adjList = createAdjacencyList();
    //std::cout << "adj List " << std::to_string(adjList.size())<< std::endl;
//    for (const std::vector<int> row : adjList) {
//        for (const int col : row) {
//            //std::cout << std::to_string(col) << " ";
//        }
//        //std::cout << std::endl;
//    }
    printAllPaths(tempStartCave->getCaveId(), tempEndCave->getCaveId(), adjList);
}

std::vector<std::vector<int> > Dungeon::createAdjacencyList() {
    std::vector<std::vector<int> > adjList(xcoordinate * ycoordinate + 1);
    for (int i = 0; i <= xcoordinate * ycoordinate; i++) {
        adjList[i] = std::vector<int>();

    }

    for (int i = 0; i < xcoordinate; i++) {
        for (int j = 0; j < ycoordinate; j++) {
            std::unordered_map<std::string, int > directionMap = caveList[i][j]->getDirection();
            for (auto& paths : directionMap) {
                // //std::cout  << "Insidde for" << paths.first << std::to_string(paths.second)<< std::endl;
                if (paths.second != 0) {
                   //  //std::cout  << "Inside path" << std::endl;
                    adjList[caveList[i][j]->getCaveId()].push_back(paths.second);
                }
            }
        }
    }

    for (const std::vector<int> row : adjList) {
        for (const int col : row) {
            //std::cout << std::to_string(col) << " ";
        }

    }

    return adjList;
}


void Dungeon::printAllPaths(int startCaveId, int endCaveId, std::vector<std::vector<int> > adjList) {
    if (startCaveId <= 0 || endCaveId <= 0 || adjList.size() <= 0) {
        throw std::invalid_argument("Invalid Input Values");
    }
    std::vector<bool> isVisited(xcoordinate * ycoordinate + 1);

    std::vector<int> pathList =  std::vector<int>();

    // add source to path[]
    pathList.push_back(startCaveId);

    // Call recursive utility
    printAllPathsUtil(startCaveId, endCaveId, isVisited, pathList, adjList);
}

void Dungeon::printAllPathsUtil(int u, int d, std::vector<bool> isVisited,
                               std::vector<int> localPathList, std::vector<std::vector<int> > adjList) {
    if (u <= 0 || d <= 0 || &localPathList == nullptr || &adjList == nullptr
        || localPathList.size() <= 0 || adjList.size() <= 0) {
        throw std::invalid_argument("Invalid inputs");
    }
    //
    if (u == d) {

        // if match found then no need to traverse more till depth

        std::vector<int> temp(localPathList);
        startEndPath.push_back(temp);
        return;

    } else {

        // Mark the current node
        isVisited[u] = true;

        // Recur for all the vertices
        // adjacent to current vertex
        for (int i : adjList[u]) {
            if (!isVisited[i]) {
                localPathList.push_back(i);
                printAllPathsUtil(i, d, isVisited, localPathList, adjList);
                localPathList.erase(localPathList.end() - 1);
            }
        }


        // Mark the current node
        isVisited[u] = false;
    }
}

std::string Dungeon::printDungeon(Cave* currentCave) {
    std::cout << "*******CHEAT MODE********" << std::endl;
    std::cout << "Yellow : Caves with Arrows" << std::endl;
    std::cout << "Green : Caves with Monster" << std::endl;
    std::cout << "Purple : Caves with Monster and Arrows" << std::endl;
    std::stringstream dungeon;
    dungeon << " ";
    for (std::vector<Cave*> list : caveList) {
        for (int i = 0; i < list.size(); i++) {
            Cave* cave = list.at(i);
            dungeon<< (cave->getDirection().at("NORTH") != 0 ? "   || " : "      ");
        }
        dungeon<< "\n";
        for (int i = 0; i < list.size(); i++) {
            Cave* c1 = list.at(i);
            std::string color = "\033[37m";
            dungeon<< (c1->getDirection().at("WEST") != 0 ? "==" : "  ");
            if (Cave* cave = dynamic_cast<Cave*>(c1)) {
                if (cave->getCaveId() == currentCave->getCaveId()) {
                    color = getOutputColour(*cave);
                    dungeon<< color << "(" << "\033[0m" << "\033[31m" << ":P" << "\033[0m"
                            << color << ")" << "\033[0m";
                } else {
                   color = getOutputColour(*cave);
                   if(cave->getDirection().at("EAST") !=0 && cave->getColumnNo() == ycoordinate - 1){
                       dungeon<< "==";
                   }
                   else {
                       if(cave->getCaveId() == endCave->getCaveId()) {
                           dungeon<<  color + "(:G)" + "\033[0m";
                       }
                       else if(cave->isTunnel()) {
                           dungeon<<  color + " TT " + "\033[0m";
                       }
                       else if(cave->getCaveId() <= 9) {
                           dungeon<<  color + "(0" + std::to_string(cave->getCaveId()) + ")" + "\033[0m";
                       }
                       else {
                           dungeon<< color + "(" + std::to_string(cave->getCaveId()) + ")" + "\033[0m";
                       }
                   }

                   // std::cout << (cave->getDirection().at("EAST") != 0 && cave->getColumnNo() == ycoordinate - 1 ? "==" : "  ");
                    //std::cout << (cave->getCaveId() == endCave->getCaveId() ? color + "(:G)" + "\033[0m" :
//                                (cave->isTunnel() ? color + "TT" + "\033[0m" :
//                                 (cave->getCaveId() <= 9 ? color + "(0" + std::to_string(cave->getCaveId()) + ")" + "\033[0m" :
//                                  color + "(" + std::to_string(cave->getCaveId()) + ")" + "\033[0m")));
                }
            }
        }
        dungeon<< "\n";
        for (int i = 0; i < list.size(); i++) {
            Cave* c1 = list.at(i);
            if (c1->getRowNo() == xcoordinate - 1) {
                dungeon<< (c1->getDirection().at("SOUTH") != 0 ? "   || " : "      ");
            }
        }
    }
    return dungeon.str();

}

std::string Dungeon::getOutputColour(Cave c1) {
    std::string colour;
    if (c1.getMonster() != nullptr && c1.isArrow()) {
        colour = "\033[35m";
    } else if (c1.getMonster() != nullptr && !c1.isArrow()) {
        colour = "\033[32m";
    } else if (c1.getMonster() == nullptr && c1.isArrow()) {
        colour = "\033[33m";
    } else {
        colour = "\033[37m";
    }
    return colour;
}

void Dungeon::updateMonsterHealth(int caveId) {
        if (caveId < 0) {
            throw std::invalid_argument("Invalid Cave Id");
        }
        for (int i = 0; i < xcoordinate; i++) {
            for (int j = 0; j < ycoordinate; j++) {
                if (caveList.at(i).at(j)->getCaveId() == caveId) {
                    int monsterId = caveList.at(i).at(j)->getMonster()->getMonsterId();
                    for (Monster* monster : monsterList) {
                        if (monster->getMonsterId() == monsterId) {
                            monster->decreaseHealth();
                        }
                    }
                }
            }
        }

}



