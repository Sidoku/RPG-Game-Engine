//
// Created by Sanjana Nalawade on 4/3/23.
//

#ifndef FINAL_RANDOM_H
#define FINAL_RANDOM_H

#include <random>

class Random {
    public:
        Random();
        /**
         * generates a random number.
         *
         * @param minNumber minimum number
         * @param maxNumber maximum number
         * @return Integer random number
         */
        int getRandomNumber(int minNumber, int maxNumber);
};
#endif //FINAL_RANDOM_H
