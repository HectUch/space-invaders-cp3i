#ifndef BARRIER_H
#include "barrier.h"
#define BARRIER_H 

barrier::barrier(float x_int, float y_int){
    
    this->x = x_int;
    this->y = y_int;
   
}

float barrier::getX(void){
    return this->x;
}

float barrier::getY(void){
    return this->y;
}

#endif
