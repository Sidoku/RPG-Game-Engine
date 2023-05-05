//
// Created by Sanjana Nalawade on 4/3/23.
//
#include "../../include/GameWorld/Cave.hpp"
#include <stdexcept>
#include <string>
#include <sstream>

Cave::Cave(int caveId, int rowNo, int columnNo) : caveId(caveId), rowNo(rowNo), columnNo(columnNo) {
    if (caveId <= 0 || rowNo < 0 || columnNo < 0) {
        throw std::invalid_argument("Input Value Cannot be Negative");
    }
    monster = nullptr;
    misArrow = false;
    misTunnel = false;
}


Cave::Cave(const Cave &cave):
        caveId(cave.caveId),
        rowNo(cave.rowNo),
        columnNo(cave.columnNo),
        caveTreasure(cave.caveTreasure),
        direction(cave.direction),
        misArrow(cave.misArrow),
        misTunnel(cave.misTunnel),
        monster(cave.monster) {}


int Cave::getCaveId() {
    return this->caveId;
}

int Cave::getRowNo() {
    return this->rowNo;
}

int Cave::getColumnNo() {
    return this->columnNo;
}

void Cave::setDirection(std::string path, int caveId) {
    if (path == "" ) {
        throw std::invalid_argument("Invalid Inputs");
    }
    direction.updatePath(path, caveId);
}

std::unordered_map<std::string, int> Cave::getDirection() {
    return direction.getPath();
}

bool Cave::isTunnel() {
    return misTunnel;
}

void Cave::setTunnel(bool tunnel) {
    misTunnel = tunnel;
}

void Cave::setCaveTreasure(std::string caveJewels, int value)  {
    if ( value < 0) {
        throw std::invalid_argument("Invalid Inputs");
    }
    caveTreasure.setJewels(caveJewels, value);
}

int Cave::getCaveTreasure(std::string caveJewels) {
    return caveTreasure.getJewels(caveJewels);
}

std::string Cave::toString() {
    std::ostringstream oss;
    oss << "CaveId: " << caveId
        << " RowNo: " << rowNo
        << " ColumnNo: " << columnNo
        << " isTunnel: " << misTunnel
        << " Arrows: " << misArrow;
    if (monster == nullptr) {
        oss << " Monster: False";
    } else {
        oss << " Monster: " << &monster;
    }
    oss << " Treasure: Diamond: " << caveTreasure.getJewels("DIAMONDS")
        << " Ruby: " << caveTreasure.getJewels("RUBY")
        << " Sapphire: " << caveTreasure.getJewels("SAPPHIRE")
        << " Direction: East: " << direction.getCavePath("EAST")
        << " West: " << direction.getCavePath("WEST")
        << " NORTH: " << direction.getCavePath("NORTH")
        << " SOUTH: " << direction.getCavePath("SOUTH");
    return oss.str();
}

bool Cave::isArrow() {
    return misArrow;
}

void Cave::setArrow(bool arrow) {
    misArrow = arrow;
}

Monster* Cave::getMonster() {
    if (monster == nullptr) {
        return nullptr;
    }
    return monster;
}

void Cave::setMonster(Monster* monster) {
    this->monster = monster;
}

bool Cave::operator==(const Cave& other) const {
    return (this->caveId == other.caveId) &&
           (this->rowNo == other.rowNo) &&
           (this->columnNo == other.columnNo) &&
            (this->misTunnel == other.misTunnel) &&
            (this->misArrow == other.misTunnel) &&
            (this->caveTreasure == other.caveTreasure) &&
            (this->direction == other.direction);
}


//TODO might be wrong
Cave::Cave() {}
