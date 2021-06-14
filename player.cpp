#ifndef PLAYER_H
#include "player.h"
#define PLAYER_H 

player::player(){    
    this->lives = 3;
    this->score = 0;
    this->x = 400;//InitialPosition
    this->y = 550;//InitalPosition   
}

void player::setPosition(float onlyX){
    this->x = onlyX;
}

int player::getLives(void ){
    return this->lives;
}

void player::wasHit(void ){
        this->lives = lives -1;
}

float player::getX(void){
    return this->x;
}

float player::getY(void){
    return this->y;
}

int player::getScore(void){
    return this->score;
}

void player::setScore(int Score){
    this->score += Score;
}

#endif
