//
// Created by Sanjana Nalawade on 4/2/23.
//

#ifndef FINAL_CAVEJEWELS_H
#define FINAL_CAVEJEWELS_H

#include <unordered_map>
#include <string>

/**
 * Cave Jewels represent the treasure in cave or with player.
 * It has treasure like diamonds, ruby, sapphire.
 */
class CaveJewels {
    public:
        CaveJewels();
        int getJewels(std::string);
        void setJewels(std::string, int);
        std::unordered_map<std::string,int> getCaveJewels();
        bool operator==(const CaveJewels& other) const;
    private:
        std::unordered_map<std::string,int> jewels;

};


#endif //FINAL_CAVEJEWELS_H
