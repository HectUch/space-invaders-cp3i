#ifndef BULLET_H
#include "bullet.h"
#define BULLET_H 

bullet::bullet(float x_int, float y_int){
    
    this->x = x_int;
    this->y = y_int;
   
}

float bullet::getX(void){
    return this->x;
}

float bullet::getY(void){
    return this->y;
}

void bullet::setPosition(float y){
        this->y = y;    
}

#endif
