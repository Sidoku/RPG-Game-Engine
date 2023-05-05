//
// Created by Sanjana Nalawade on 4/4/23.
//

#ifndef FINAL_GAMEMODEL_H
#define FINAL_GAMEMODEL_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "enums/CaveJewels.h"
#include "Player.h"
#include "Random.h"
#include "Cave.hpp"
#include "Dungeon.h"


class GameModel {
    public:
        GameModel(int xcoordinate, int ycoordinate, int interconnectivity, bool isWrapping,
              int treasurePercentage, int monsterCount, std::string playerName, int pix);

        /**
         * printMaze method calls teh dungeon's print Dungeon method and returns the string to the dirver
         * the Dungeon in string format, with each cave represented by "()" with cave numbers,
         * tunnels represented by TT and the player, and End or Goal represented
         * by (:P) and (:G) respectively.In the dungeon std::string, == represents horizontal connections
         * and || represents vertical connections.
         *
         * @return std::string
         */
        std::string printMaze();

        /**
         * Checks if the player current location is equal to the end cave and returns bool value.
         *
         * @return bool value
         */
        bool checkWinning();

        /**
         * available path returns teh possible paths from the current cave in std::string format to the user.
         * It gets this my calling the current cave direction hashmap  and performing operation on it.
         *
         * @return std::string of available path
         */
        std::string availablePaths();

        /**
         * check vaiid move takes the move string as input and returns a bool value after checking
         * if it's a valid string of acceptable move in the direction enumeration.
         *
         * @param move Move std::string
         * @return Boolean result
         */
        bool checkValidMove(std::string move);

        /**
         * Move to position method takes the move string as input and checks which is teh neighbouring
         * cave in that direction by calling the get direction method of teh cave. It updates the player
         * current location and then updates the current cave.
         *
         * @param move std::string move
         */
        void moveToPosition(std::string move);

        /**
         * available Treasure returns the treasure available in the current cave, by checking if there
         * are any non-zero values in the hashmap of cave treasure.
         *
         * @return std::string of result
         */
        std::string availableTreasure();

        /**
         * Maze details returns the start and end cave that is the start and goal of the player.
         *
         * @return Integer Array of start and end cave id.
         */
         std::vector<int> mazeDetails();

        /**
         * Player location details returns the players current location, that is in which cave the player
         * is at the very moment. Is it a cave or Tunnel and its number.
         *
         * @return int cave id
         */
        std::vector<std::string> playerLocationDetails();

        /**
         * Player Treasure details returns the total treasure collected by the player.
         *
         * @return Hashmap of Treasure and integer Value.
         */
        CaveJewels playerTreasureDetails();

        /**
         * Check Treasure in cave returns true if the current cave has any treasureelse return false.
         *
         * @return bool
         */
        bool checkTreasureInCave(Cave* cave);

        /**
         * pick up treasure updates the player's treasure by adding the current cave treasure to
         * it treasure collection and makes the current cave treasure 0.
         */
        void pickupTreasure(std::string caveJewels);

        /**
         * Checks the cave object's isArrow attribute to see if it has an arrow.
         *
         * @return bool value true or false.
         */
        bool checkArrow(Cave* cave);

        /**
         * The player's arrow count is increased by one, and the cave object is activated. False arrow
         */
        void pickupArrow();

        /**
         * When a player shoots from the current cave, the cave count and direction for the arrow
         * to be shot are displayed. The arrow moves to the cave that is at a distance of cave
         * count from the current cave in the direction specified by the player; if there is a tunnel,
         * the direction is changed according to the exit of the tunnel. It checks to see if the
         * monster is present in the destination cave and, if so, either updates its health or informs
         * the player that the arrow was shot into the darkness.
         *
         * @param move  Direction of arrow to move
         * @param count Count of caves the arrow can move
         * @return Result std::string
         */
        std::string shoot(std::string move, int count);

        /**
         * The more pungent smell string is returned if a monster is present at a distance of one from
         * the player's current location. In addition, if two monsters are present at a distance of
         * two from the player's current location, the more pungent smell string is returned.
         * However, if only one monster is present within a 2-mile radius of the player's current
         * location, the less pungent smell std::string is returned.
         *
         * @return Result std::string
         */
        std::string smell();

        /**
         * If the player's current location has a monster with a health of 2, the player is eaten
         * by the Otyugh; if the monster's health is 1, the player has a 50% chance of survival;
         * and if there is no monster, the player is alive.
         *
         * @return Boolean Value
         */
        bool isPlayerAlive();

        /**
         * Checks to see if the player has any arrows with which to shoot.
         *
         * @return bool value
         */
        bool checkPlayerArrow();

        /**
         * Returns the number of arrows currently in the player's possession.
         *
         * @return int arrow count
         */
        int playerArrowDetails();

        /**
         * Returns the copy of the Dungeon in the list of list format.
         *
         * @return dungeons in list of list of caves.
         */
        std::vector<std::vector<Cave*> > getCaveList();

        /**
         * Returns the player Name.
         *
         * @return player name
         */
        std::string getPlayerName();

        /**
         * Returns the set of integers which consist of all teh caves and tunnels that are visited by the
         * player.
         *
         * @return Sets of Integers consisting of cave id of caves visited by player.
         */
        std::set<int> getVisitedCave();

        int getPix();

        int getBoardRow();

        int getBoardCol();

        std::unordered_map<int,int> getCaveWithTreasure();
        Cave* getCave(int caveId);
        Cave* currentCave;
        bool quit=false;
        std::vector<int> getEndcave();
        int  getRandomValue(int min, int max);
        void setPlayerdiceRoll(int val);
        int getPlayerdiceRoll();
       std::string playerDetails();

    private:
        int m_pix;
        Dungeon* dungeon;
        Player* player;
        Random random;
        std::set<int>visitedCave;
        std::string helperSmell(std::vector<std::vector<int> > helperList);
        std::vector<std::vector<int> > helperList();
        int boardRow;
        int boardCol;


};

#endif //FINAL_GAMEMODEL_H
