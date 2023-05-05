#include "../include/ControllerComponent.hpp"
#include <iostream>

ControllerComponent::ControllerComponent(TransformComponent* transformComponent1, TransformComponent* transformComponent2,
                                         TransformComponent* transformComponent3,TransformComponent* transformComponent4,
                                         TransformComponent* transformComponent5, TransformComponent* transformComponent6,
                                         TransformComponent* transformComponent7,
                                         AudioComponent* audioComponent, GameModel* model)
                                         :t_transformComponent(transformComponent1) ,
                                          a_transformComponent(transformComponent2) ,
                                          m_transformComponent(transformComponent3),
                                          p_transformComponent(transformComponent4),
                                          d_transformComponent(transformComponent5),
                                          txt_transformComponent(transformComponent6),
                                          ss_transformComponent(transformComponent7),
                                          audioComponent(audioComponent),
                                          model(model){
}

ControllerComponent::~ControllerComponent(){
}


void ControllerComponent::Update() {
    // Check keyboard input to modify position
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    int x = m_transformComponent->GetX();
    int y = m_transformComponent->GetY();
    //m_transformComponent->SetLastPosition(x,y);
    //p_transformComponent->SetAnimType("idle");
    char move = '0';
    bool soundPlay = false;
    bool quit = false;
    std::string shoot ="";

                                        
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            std::cout<< "quit" << std::endl;
            model->quit = true;
            break;
        }
        switch (e.type) {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_s:
                    case SDLK_DOWN:
                        if(shootArrow) {
                            shootDirection = true;
                            move = 'S';
                        }
                        else if (ismove  && model->checkValidMove("SOUTH")) {
                            p_transformComponent->SetAnimType("walk");
                            move = 'S';
                            std::cout << "S" << std::endl;
                        }
                        break;
                    case SDLK_l :
                        if(!diceRoll){
                            std::cout << "Starting dice roll" << std::endl;
                            d_transformComponent->SetY(1);
                            diceRoll = true;
                            audioComponent->playSound("Dice 01");
                            soundPlay=true;
                        }else{
                            std::cout << "Stopping dice roll" << std::endl;
                            int rol_value = model->getRandomValue(1,6);
                            model->setPlayerdiceRoll(rol_value);
                            d_transformComponent->SetX(rol_value);
                            d_transformComponent->SetY(0);
                            diceRoll = false;
                            ismove = true;
                            shoot = "";
                        }
                        break;
                    case SDLK_w:
                    case SDLK_UP:
                        if(shootArrow) {
                            shootDirection = true;
                            move = 'W';
                        }
                        else if (ismove  && model->checkValidMove("NORTH")) {
                           p_transformComponent->SetAnimType("walk");
                            move = 'W';
                        }
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        if(shootArrow) {
                            shootDirection = true;
                            p_transformComponent->SetAnimType("attack_left");
                            move = 'A';
                        }
                        else if (ismove  && model->checkValidMove("WEST")) {
                            p_transformComponent->SetAnimType("walk");
                            move = 'A';
                        }
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        if(shootArrow) {
                            shootDirection = true;
                            move = 'D';
                            p_transformComponent->SetAnimType("attack_right");
                        }
                        else if (ismove  && model->checkValidMove("EAST")) {
                            p_transformComponent->SetAnimType("walk");
                            move = 'D';
                        }
                        break;
                    case SDLK_p :
                        if (model->getPlayerdiceRoll() > 0){
                        std::cout << "trying to pick" << std::endl;
                        model->setPlayerdiceRoll(model->getPlayerdiceRoll() - 1);
                        if(t_transformComponent->getTname() == "treasure"){
                            std::cout<< "Trerasure pick" << std::endl;
                            if(model->checkTreasureInCave(model->currentCave)) {
                                model->pickupTreasure("DIAMONDS");
                                model->pickupTreasure("RUBY");
                                model->pickupTreasure("SAPPHIRE");
                            }
                            audioComponent->playSound("coin");
                            soundPlay = true;
                            t_transformComponent->UnSetPosition(model->currentCave->caveId);
                        }
                        }
                        break;
                    case SDLK_r :
                        if (model->getPlayerdiceRoll() > 0){
                            model->setPlayerdiceRoll(model->getPlayerdiceRoll() - 1);
                            std::cout << "trying to pick arrow" << std::endl;
                            if(a_transformComponent->getTname() == "arrow"){
                                std::cout<< "Arrow pick" << std::endl;
                                if(model->checkArrow(model->currentCave)) {
                                    model->pickupArrow();
                                }
                                audioComponent->playSound("item-equip");
                                soundPlay = true;
                                a_transformComponent->UnSetPosition(model->currentCave->caveId);
                            }
                        }
                        break;
                    case SDLK_SPACE :
                        if (model->getPlayerdiceRoll() > 0) {
                            model->setPlayerdiceRoll(model->getPlayerdiceRoll() - 1);
                            std::cout << "trying to shoot arrow" << std::endl;
                            shootArrow = true;
                            audioComponent->playSound("Arrow");
                            soundPlay = true;
                        }
                        break;



                }
                break;
        }
    }
    std::string mc = "";
    bool flag = false;
    switch (move) {
        case 'W' :
//                x -= m_moveSpeed;
            //  m_transformComponent->SetPosition(x-m_moveSpeed, y);
            mc = "NORTH";
            flag = true;
            std::cout << "X: " << x << std::endl;
            std::cout << "Y: " << y << std::endl;
            break;
        case 'A':
           // y -= m_moveSpeed;
            //  m_transformComponent->SetPosition(x, y-m_moveSpeed);
            mc = "WEST";
            flag = true;
            std::cout << "X: " << x << std::endl;
            std::cout << "Y: " << y << std::endl;
            break;
        case 'S' :
           // x += m_moveSpeed;
            //   m_transformComponent->SetPosition(x+m_moveSpeed, y);
            mc = "SOUTH";
            flag = true;
            std::cout << "X: " << x << std::endl;
            std::cout << "Y: " << y << std::endl;
            break;
        case 'D' :
            //y += m_moveSpeed;
            std::cout << "X: " << x << std::endl;
            std::cout << "Y: " << y << std::endl;
            //       m_transformComponent->SetPosition(x, y+m_moveSpeed);
            mc = "EAST";
            flag = true;
            break;
    }

    if(shootArrow && shootDirection){
        if (model->checkPlayerArrow()) {
            std::cout << "Shooting Arrow  : " << mc <<std::endl;
            shoot = "\n-------------\n" + model->shoot(mc,1);
            int cvId = model->currentCave->getDirection()[mc];
            std::cout << "Shooting Cave  : " << cvId <<std::endl;
            //std::cout << "Monster Cave  : " << model->getCave(cvId)->getMonster() <<std::endl;
            if(model->getCave(cvId)->getMonster() == nullptr){
                std::cout << "start Cave  : "  <<std::endl;
                m_transformComponent->UnSetPosition(cvId);
                std::cout << "Done Cave  : "  <<std::endl;
            }
        }

        shootArrow = false;
        shootDirection= false;
    }else if (flag && !shootArrow && model->getPlayerdiceRoll() > 0) {
        model->moveToPosition(mc);
//        std::cout << "Current Cave : x" << model->currentCave->getRowNo() << " y:  "
//                  << model->currentCave->getColumnNo() << "\nCx: " << x << " Cy:" << y << std::endl;
        std::cout << model->printMaze() << std::endl;
        std::cout << "Player Roll " << model->getPlayerdiceRoll() << std::endl;
        model->setPlayerdiceRoll(model->getPlayerdiceRoll() -1);
        flag = false;
    }


    if(p_transformComponent->getTname() == "player" ) {

        p_transformComponent->SetPosition(model->currentCave->getRowNo(), model->currentCave->getColumnNo());
    }

//std::cout << "Player Roll " << model->getPlayerdiceRoll() << std::endl;
    if(model->getPlayerdiceRoll() < 0){
        model->setPlayerdiceRoll(0);
    }


if(model->checkWinning()) {


}else if(shoot != "") {
    std:: string det = model->playerDetails() +"\n"
            + shoot;
    std::cout << det <<std::endl;
    txt_transformComponent->setDetailsText(det);

}else{
    txt_transformComponent->setDetailsText(model->playerDetails());
}

if(model->smell() == "You smell something \n more pungent nearby "){
    audioComponent->playSound("monsterSound");
    soundPlay = true;
}
//if(!soundPlay){
//    audioComponent->playSound("bgMusic");
//}

}




