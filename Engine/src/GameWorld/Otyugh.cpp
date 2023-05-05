//
// Created by Sanjana Nalawade on 4/4/23.
//

#include "../../include/GameWorld/Otyugh.hpp"
#include <stdexcept>

Otyugh::Otyugh(int monsterId) : monsterId(monsterId) {
    if (monsterId <= 0) {
        throw std::invalid_argument("Invalid Monster Id");
    }
    health = 2;
}

Otyugh::Otyugh(Monster *monster) {
    if (monster == nullptr) {
        throw  std::invalid_argument("Monster Cannot Be Null");
    }
    monsterId = monster->getMonsterId();
    health = monster->getHealth();
}

int Otyugh::getHealth() const {
    return health;
}

void Otyugh::decreaseHealth() {
    if (health == 0) {
        throw std::invalid_argument("Monster is dead cannot damage more");
    }
    health--;
}

int Otyugh::getMonsterId() const {
    return monsterId;
}