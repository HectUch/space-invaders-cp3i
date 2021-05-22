#ifndef INVADERS_H
#include "invader.h"
#define INVADERS_H 

invader::invader(){
    
    this->lives = 3;
    this->score = 3;
    this->x = 400;
    this->y = 500;
   
}

int invader::getScore(void){
    return this->score;
}

float invader::getX(void){
    return this->x;
}

float invader::getY(void){
    return this->y;
}


#endif
