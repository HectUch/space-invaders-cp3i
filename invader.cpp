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


void invader::setPosition(float x,float y){
    this->x = x;
    this->y = y;
    
}

bool invader::isAlive(){
    
    if(this->lives <= 0)
        return false;
    else
        return true;
    
}

void invader::getHit(){
        this->lives = 0;
        this->type = 'F';
}


void invader::setScore(int Score){
    this->score += Score;
}

int invader::getScore(void){
    this->getHit();
    return this->score;
}

float invader::getX(void){
    return this->x;
}

float  invader::getY(void){
    return this->y;
}


int invader::getLives(void ){
    return this->lives;
}

void invader::wasHit(void ){
        this->lives = lives -1;
}

void invader::recruitToWar(int score,char type){
    
    this->lives = 1;
    this->score = score;
    this->type = type;
    
}

char invader::getType(void){
    return this->type;
}

void invader::setType(char q){
        this->type = q;
}

#endif
