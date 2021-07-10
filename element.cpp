#ifndef ELEMENT_CPP
#include "element.h"
#define ELEMENT_CPP


void element::setPosition(float x,float y){
    this->x = x;
    this->y = y;
    
}

bool element::isAlive(){
    
    if(this->lives <= 0)
        return false;
    else
        return true;
    
}

void element::getHit(){
        this->lives = 0;
        this->type = 'F';
}


void element::setScore(int Score){
    this->score += Score;
}

int element::getScore(void){
    this->getHit();
    return this->score;
}

float element::getX(void){
    return this->x;
}

float  element::getY(void){
    return this->y;
}

void element::setPosition(float onlyX){
     if(onlyX < 0 || onlyX > 755)
         return;
        
    this->x = onlyX;
}

int element::getLives(void ){
    return this->lives;
}

void element::wasHit(void ){
        this->lives = lives -1;
}


#endif
