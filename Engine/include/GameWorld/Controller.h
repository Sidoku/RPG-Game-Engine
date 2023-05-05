//
// Created by Sanjana Nalawade on 4/4/23.
//

#ifndef FINAL_CONTROLLER_H
#define FINAL_CONTROLLER_H

#include "GameModel.h"

class Controller {
    public :
        Controller(GameModel model);
        void start() ;
    private:
        GameModel model;
        void playerDetails(std::string playerName);
        int menu();
        void winning(std::string playerName);
        void move();
        void pickup();
        void shoot();
};
#endif //FINAL_CONTROLLER_H
