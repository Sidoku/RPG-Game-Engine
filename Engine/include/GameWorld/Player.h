//
// Created by Sanjana Nalawade on 4/2/23.
//

#ifndef FINAL_PLAYER_H
#define FINAL_PLAYER_H

#include "enums/CaveJewels.h"
#include <string>
class Player{
    public:
        Player(std::string playerName, int playerLocation);
        /**
        * Set Treasure Count updates the player treasure by adding the passed
        * treasure to it current treasure.
        *
        * @param caveJewels      Treasure to be updated
        * @param count treasure count.
        */
        void setTreasureCount(std::string caveJewels, int count);

        /**
         * Returns the players treasure of respective type from the hash map.
         *
         * @param caveJewels treasure
         * @return int count
         */
        int getTreasureCount(std::string caveJewels);

        /**
         * get player location returns the current position of the cave that is in which cave it is in.
         *
         * @return integer cave id
         */
        int getPlayerLocation();

        /**
         * sets the player location when the player moves to next cave. It sets it to the cave id that is
         * passed as input to this method.
         *
         * @param nextCaveId Integer cave id
         */
        void setPlayerLocation(int nextCaveId);

        /**
         * Returns the Arrows that are currently with the player.
         *
         * @return int arrow count.
         */
        int getArrowCount();

        /**
         * Updates the arrow count with the player by adding arrows when the player picks them up
         * from the caves and subtracting arrows when the player shoots arrows.
         *
         * @param conditionForAddorSub Boolean value if true add arrow if false reduce arrow count by 1.
         */
        void updateArrowCount(bool conditionForAddorSub);

        /**
         * Returns the player Name to the controller.
         * @return String
         */
        std::string getPlayerName();
        std::string toString();

        void setDiceRoll(int val);
        int getDiceRoll();

    private:
        std::string playerName;
        int playerLocation;
        CaveJewels treasureCount;
        int arrowCount;
        int dice_roll = 0;
};
#endif //FINAL_PLAYER_H
