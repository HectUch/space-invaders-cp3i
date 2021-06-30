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
    this->type = 'B';
   
}

char invader::getType(void){
        return this->type;
}

void invader::setType(char q){
        this->type = q;
}

#endif
