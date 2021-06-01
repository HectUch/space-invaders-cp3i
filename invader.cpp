#ifndef INVADERS_H
#include "invader.h"
#define INVADERS_H 

invader::invader(float x,float y,char type){
    
    this->lives = 1;
    this->score = 10;
    this->x = x;
    this->y = y;
    this->type = type;
   
}


invader::invader(){
    
    this->lives = 1;
    this->score = 10;
    this->x = 400;
    this->y = 500;
   
}

void invader::getHit(){
        this->lives = 0;
}
void invader::setPosition(float x,float y){
    this->x = x;
    this->y = y;
    
}

char invader::getType(void){
    return this->type;   
}

bool invader::isAlive(){
    
    if(this->lives <= 0)
        return false;
    else
        return true;
    
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
