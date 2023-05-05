//
// Created by Sanjana Nalawade on 4/3/23.
//

#ifndef FINAL_OTYUGH_HPP
#define FINAL_OTYUGH_HPP
#include "Monster.hpp"
class Otyugh : public Monster {
    public:
        Otyugh(int monsterId);
        /**
        * Its a copy constructor to create copy of monster object.
        *
        */
        Otyugh(Monster *monster);
        int getHealth() const override;
        void decreaseHealth() override;
        int getMonsterId() const override;
    private:
        int monsterId;
        int health;
};
#endif //FINAL_OTYUGH_HPP
