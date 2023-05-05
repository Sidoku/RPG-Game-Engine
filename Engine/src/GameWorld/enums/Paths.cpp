//
// Created by Sanjana Nalawade on 4/6/23.
//

#include "../../../include/GameWorld/enums/Paths.h"
#include "iostream"
#include <stdexcept>

Paths::Paths() {
    path_map = std::unordered_map<std::string,int>();
    path_map.insert(std::make_pair("EAST", 0));
    path_map.insert(std::make_pair("NORTH", 0));
    path_map.insert(std::make_pair("SOUTH", 0));
    path_map.insert(std::make_pair("WEST", 0));
}

void Paths::updatePath(std::string path, int val) {
    for (const auto& pair : path_map) {
//        std::cout << pair.first << " : " << pair.second << std::endl;
        if(pair.first == path) {
            path_map[pair.first] = val;
        }

    }
}

int Paths::getCavePath(std::string path) {
    for (const auto& pair : path_map) {
//        std::cout << pair.first << " : " << pair.second << std::endl;
        if(pair.first == path) {
            return pair.second;
        }
    }
    throw std::runtime_error("No Path found");
}


std::unordered_map<std::string,int> Paths::getPath() {
    return path_map;
}

bool Paths::operator==(const Paths& other) const {
    return (this->path_map.find("NORTH")->second == other.path_map.find("NORTH")->second) &&
           (this->path_map.find("SOUTH")->second == other.path_map.find("SOUTH")->second) &&
            (this->path_map.find("EAST")->second == other.path_map.find("EAST")->second) &&
           (this->path_map.find("WEST")->second == other.path_map.find("WEST")->second);
}