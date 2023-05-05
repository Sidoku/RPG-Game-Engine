//
// Created by Sanjana Nalawade on 4/4/23.
//

#include "../../include/GameWorld/Random.h"
Random::Random() {}
int Random::getRandomNumber(int minNumber, int maxNumber) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(minNumber, maxNumber);
    return distribution(generator);
}



