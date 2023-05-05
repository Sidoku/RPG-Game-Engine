//
// Created by Sanjana Nalawade on 4/2/23.
//

#ifndef FINAL_MONSTER_HPP
#define FINAL_MONSTER_HPP
class Monster {
    public:

        ~Monster(){};
        /**
        * Monsters' health is restored. The monster's health is set to 2 by default,
        * and it is affected if a player shoots an arrow at it.
        *
        * @return int monster health count.
        */
        virtual int getHealth() const= 0;

        /**
         * When a player shoots an arrow at a monster, its health is reduced by one.
         */
        virtual void decreaseHealth() =0;

        /**
         * The Monster Id is returned.
         *
         * @return int monster ID.
         */
        virtual int getMonsterId() const =0;
};
#endif //FINAL_MONSTER_HPP
