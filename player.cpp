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


bool player::isAlive(){    
    if(this->lives <= 0)
        return false;
    else
        return true;    
}

void player::getHit(){
        this->lives = 0;
        this->type = 'F';
    
}


void player::setScore(int Score){
    this->score += Score;
}


float player::getX(void){
    return this->x;
}

float  player::getY(void){
    return this->y;
}

void player::setPosition(float onlyX){
     if(onlyX < 0 || onlyX > 755)
         return;
        
    this->x = onlyX;
}

int player::getLives(void ){
    return this->lives;
}

void player::wasHit(void ){
        this->lives = lives -1;
}



#endif
