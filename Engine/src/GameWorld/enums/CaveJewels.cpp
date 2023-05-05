//
// Created by Sanjana Nalawade on 4/6/23.
//
#include <iostream>
#include <stdexcept>
#include "../../../include/GameWorld/enums/CaveJewels.h"
CaveJewels::CaveJewels() {
    jewels = std::unordered_map<std::string, int>();
    jewels.insert(std::make_pair("DIAMONDS",0));
    jewels.insert(std::make_pair("RUBY",0));
    jewels.insert(std::make_pair("SAPPHIRE",0));

}

int CaveJewels::getJewels(std::string jewel) {
    for (const auto& pair : jewels) {
//        std::cout << pair.first << " : " << pair.second << std::endl;
        if(pair.first == jewel) {
            return pair.second;
        }
    }
    throw std::runtime_error("Jewel doesn't exist");
}
void CaveJewels::setJewels(std::string jewel, int val) {
    for (const auto& pair : jewels) {
//        std::cout << pair.first << " : " << pair.second << std::endl;
        if(pair.first == jewel) {
            jewels[pair.first] = val;
        }
    }
}

std::unordered_map<std::string,int> CaveJewels::getCaveJewels()  {
    return jewels;
}


bool CaveJewels::operator==(const CaveJewels& other) const {
    return (this->jewels.find("DIAMONDS")->second == other.jewels.find("DIAMONDS")->second) &&
            (this->jewels.find("RUBY")->second == other.jewels.find("RUBY")->second) &&
            (this->jewels.find("SAPPHIRE")->second == other.jewels.find("SAPPHIRE")->second);
}