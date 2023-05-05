//
// Created by Sanjana Nalawade on 4/4/23.
//

#include "../../include/GameWorld/Player.h"
#include <stdexcept>
#include <string>
#include <sstream>

Player::Player(std::string playerName, int playerLocation) : playerName(playerName), playerLocation(playerLocation)  {
        if (playerName == " " || playerName == "") {
            throw std::invalid_argument("Invalid Player Name");
        }
        if (playerLocation <= 0) {
            throw std::invalid_argument("Invalid Player Location");
        }
        arrowCount = 3;
}


std::string Player::toString() {
    std::ostringstream sb;
    sb << "Player Name: " << playerName;
    sb << "\n Current Location : " << playerLocation;
    sb << "\n *****:Treasure:***** \n  Diamond: " << treasureCount.getJewels("DIAMONDS");
    sb << " Sapphire: " << treasureCount.getJewels("SAPPHIRE");
    sb << " Ruby: " << treasureCount.getJewels("RUBY");
    return sb.str();
}


std::string Player::getPlayerName() {
    return playerName;
}


void Player::setTreasureCount(std::string caveJewels, int count) {
    if (caveJewels == "") {
        throw std::invalid_argument("Invalid Inputs");
    }
    treasureCount.setJewels(caveJewels, treasureCount.getJewels(caveJewels) +count);

}


int Player::getTreasureCount(std::string caveJewels) {
    return treasureCount.getJewels(caveJewels);
}


int Player::getPlayerLocation() {
    return playerLocation;
}


void Player::setPlayerLocation(int playerLocation) {
    if (playerLocation <= 0) {
        throw std::invalid_argument("Invalid playerLocation as input");
    }
    playerLocation = playerLocation;
}


int Player::getArrowCount() {
    return arrowCount;
}


void Player::updateArrowCount(bool conditionForAddorSub) {
    if (conditionForAddorSub) {
        arrowCount = arrowCount + 1;
    } else {
        if (arrowCount != 0) {
            arrowCount = arrowCount - 1;
        } else {
            throw std::runtime_error("Cannot Decreases Arrow Count");
        }
    }
}

void Player::setDiceRoll(int val) {
    this->dice_roll = val;
}
int Player::getDiceRoll() {
    return this->dice_roll;
}