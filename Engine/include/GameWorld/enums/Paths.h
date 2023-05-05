//
// Created by Sanjana Nalawade on 4/2/23.
//

#ifndef FINAL_PATHS_H
#define FINAL_PATHS_H

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <string>
#include <unordered_map>
/**
 * The direction enumeration represents the direction from the cave,
 * such as North, South, East, and West.
 */


class Paths {
public:
    Paths();
    int getCavePath(std::string);
    void updatePath(std::string, int);
    std::unordered_map<std::string,int>  getPath();
    bool operator==(const Paths& other) const;
private :
    std::unordered_map<std::string,int> path_map;
};











#endif //FINAL_PATHS_H
