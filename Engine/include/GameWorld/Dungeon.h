//
// Created by Sanjana Nalawade on 4/4/23.
//

#ifndef FINAL_DUNGEON_H
#define FINAL_DUNGEON_H

#include <vector>
#include <string>
#include <unordered_set>
#include "Cave.hpp"
#include "Random.h"
#include "Monster.hpp"


class Dungeon {
    
    public:
        Dungeon(int xcoordinate, int ycoordinate, int interconnectivity,
            int treasurePercentage, bool isWrapping1, int monsterCount,
            Random* random);

        /**
         * Get the Cave std::vector Makes a copy of the original list and returns it.
         * The grid is represented by the cave list. It includes a list of all caves and tunnels.
         *
         * @return Copy of  cave std::vector
         */
        std::vector<std::vector<Cave*> > getCaveList();

        /**
         * Get Start Cave returns the start cave that was set by the dungeon during its construction.
         * It creates a copy of the start cave and returns it.
         *
         * @return copy of Start Cave.
         */
        Cave* getStartCave();

        /**
         * Get End Cave returns the end cave that was set by the dungeon during its construction.
         * It creates a copy of the end cave and returns it.
         *
         * @return copy of End Cave;
         */
        Cave* getEndCave();

        /**
         * Returns the Dungeon in string format, with each cave represented by "()" with cave numbers,
         * tunnels represented by TT and the player, and End or Goal represented
         * by (:P) and (:G) respectively.In the dungeon String, == represents horizontal connections
         * and || represents vertical connections.
         *
         * @param currentCave Current Cave
         * @return String of Dungeon or Maze
         */
        std::string printDungeon(Cave* currentCave);

        /**
         * Get Cave accepts a cave Id and searches the cave list for the cave with the given cave Id,
         * returning a copy of that cave.
         *
         * @param nextCaveId Cave Id
         * @return Cave Object
         */
        Cave* getCave(int nextCaveId);

        /**
         * Update Treasure accepts the cave object and searches the cave
         * list for an equivalent cave object to update its treasure.
         *
         * @param cave Cave Object.
         */
        void updateTreasure(Cave* cave, std::string caveJewels);

        /**
         * Updates the Cave Arrow Count; because each cave can only have one arrow,
         * the bool value isArrow associated with the cave is updated.
         *
         * @param cave Cave Object
         */
        void updateArrow(Cave* cave);

        /**
         * Slays the Monster by making the monster object of the cave null.
         *
         * @param nextCaveId Cave ID
         */
        void slayMonster(int nextCaveId);

        /**
         * Updates When an arrow hits a monster, its health is reduced by one.
         * If the monster's health reaches zero, the monster dies.
         * It takes two arrows to kill a monster.
         *
         * @param caveId Cave Id
         */
        void updateMonsterHealth(int caveId);

    private:
        int xcoordinate;
        int ycoordinate;
        int interconnectivity;
        int treasurePercentage;
        int monsterCount;
        bool isWrapping;
        bool flagStartEndAssigned;
        Cave* startCave;
        Cave* endCave;
        std::vector<std::vector<Cave*> > caveList;
        std::vector<Monster*> monsterList;
        std::vector<std::vector<Cave*> > possiblePath;
        std::vector<std::vector<Cave*> > leftOverList;
        std::vector<std::vector<int> > startEndPath;
        Random random;

        void initializeDungeon();
        void initializeCave();
        void createPossiblePathList();
        void createLinks(std::vector<std::unordered_set<int> >);
        std::vector<std::unordered_set<int> >createSets();
        void updateTunnel();
        void selectStartEndCave();
        void initializeTreasureArrow(int elementPercent, std::string elementType);
        void initializeMonsters();
        std::unordered_set<int> getSets(std::vector<std::unordered_set<int> >& hashSetList, int caveId);
        void updateCaveDirection(std::vector<Cave*> possiblePath1);
        void connectLeftover();
        Cave* getCaveObject();
        void checkDistance(Cave* tempStartCave, Cave* tempEndCave);
        std::vector<std::vector<int> > createAdjacencyList();
        void printAllPaths(int startCaveId, int endCaveId, std::vector<std::vector<int> > adjList);
        void printAllPathsUtil(int u, int d, std::vector<bool> isVisited,
                                    std::vector<int> localPathList, std::vector<std::vector<int> > adjList);
        std::string getOutputColour(Cave c1);
};
#endif //FINAL_DUNGEON_H
