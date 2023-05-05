//
// Created by Sanjana Nalawade on 4/2/23.
//

#ifndef FINAL_CAVE_H
#define FINAL_CAVE_H

#include "enums/Paths.h"
#include "enums/CaveJewels.h"
#include "Monster.hpp"
#include "Otyugh.hpp"
#include <unordered_map>


class Cave  {
public:
    Cave(int caveId, int rowNo, int columnNo);
    Cave(const Cave &cave);

    Cave();

    /**
    * The cave ID is a unique attribute to each cave.
    * The cave id of that cave object is returned as an integer in getCaveId.
    *
    * @return Integer Cave Id
    */
    int getCaveId();

    /**
     * Row No is the row position of the cave in the maze or dungeon,
     * and getRowNo returns the row number of that cave object as an integer.
     *
     * @return Integer Row Number
     */
    int getRowNo();

    /**
     * The column position of the cave in the maze or dungeon is given by column No.
     * ColumnNo returns the column number of that cave object as an integer.
     *
     * @return Integer Column Number
     */
    int getColumnNo();

    /**
     * Tunnels are caves that only have two doors or directions. isTunnel is used to represent
     * tunnels.
     * setTunnel Method sets the object's boolean value to the boolean value passed to it.
     *
     * @param tunnel boolean value for tunnel.
     */
    void setTunnel(bool tunnel);

    /**
     * Tunnels are caves that only have two doors or directions. isTunnel is used to
     * represent tunnels.
     * The IsTunnel method returns a boolean value indicating whether or not the object is a tunnel.
     *
     * @return boolean value.
     */
    bool isTunnel();

    /**
     * If there is a path between them, the cave object in its direction hash map holds the
     * caveid at that position.
     * setDirection changes the value of caveID in the hashmap at the specified
     * position/direction.
     *
     * @param paths Direction
     * @param caveId    Cave Id
     */
    void setDirection(std::string path, int caveId);

    /**
     * If there is a path between them, the cave object in its direction hash map holds
     * the caveid at that position.
     * This hash map is returned by getDirection for use in further logic in the program.
     *
     * @return Hash Map of Direction and their associated cave Id
     */
    std::unordered_map<std::string, int>  getDirection();

    /**
     * The Treasure in the Cave object represents the current object's various Treasure Caves.
     * Depending on the type of Treasure, the value of each Treasure is stored in a specific
     * position in the HashMap.
     * setCaveTreasure adds the new value to the old value to update the value of the treasure
     * count of the respective treasure.
     *
     * @param caveJewels Treasure type
     * @param value    Treasure Value
     */
    void setCaveTreasure(std::string caveJewels, int value);

    /**
     * The Treasure in the Cave object represents the current object's various Treasure Caves.
     * Depending on the type of Treasure, the value of each Treasure is stored in a
     * specific position in the HashMap.
     * This hash map is returned by getCaveTreasure for use in further logic in the program.
     *
     * @return Hash Map of Treasure and its value.
     */
    int getCaveTreasure(std::string  caveJewels);

    /**
     * Checks to see if the cave has any arrow.
     *
     * @return boolean value
     */
    bool isArrow();

    /**
     * When the player selects an arrow, the arrows are set to false.
     *
     * @param arrow Arrow
     */
    void setArrow(bool arrow);

    /**
     * Returns a copy of the monster object that is present in the cave, or null if there
     * is no monster in the cave.
     *
     * @return monster object
     */
    Monster* getMonster();

    /**
     * When the player slays the monster with two arrows, the monster is set to null.
     *
     * @param monster Monster object
     */
    void setMonster(Monster* monster);

    std::string toString();
    bool operator==(const Cave& other) const;
    int caveId;

private:
    int rowNo;
    int columnNo;
    CaveJewels caveTreasure;
    Paths direction;
    bool misTunnel;
    bool misArrow;
    Monster* monster;
};
#endif //FINAL_CAVE_H
