#ifndef PLAYER_CPP
#include "player.h"
#define PLAYER_CPP

player::player(){    
    this->lives = 3;
    this->score = 0;
    this->x = 400;//InitialPosition
    this->y = 550;//InitalPosition   
}


int player::getScore(void){
    return this->score;
}


#endif
