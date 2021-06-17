#ifndef GAMEENGINE_H
#include <SFML/Audio.hpp>
#include "ScreenGen.h"
#include "element.h"
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include "gameEngine.h"
#include <vector>
#include <cmath>
#define GAMEENGINE_H

gameEngine::gameEngine(){
    
    //Sound Initialization
    sound = new sf::Sound();
    buffer = new sf::SoundBuffer();    
    initSound( );
    
    pause = false;
    //Game logic initialization
   gamer = new player();
   float invaderX = 40.f;
   float invaderY = 40.f;
   char tipo = 'C';
   randomShootingTime = 20;
   lastShoot = 0;
   timesOneSide = 0;

   
    for(int i = 0;i < 5;i++)
   {
       if(i > 1 && i < 3)
           tipo = 'A';
       else if(i >= 3)
           tipo = 'B';
        for(int j = 0;j < 11;j++)
        {
            //point =60.0+30*i;
            invaderX = (20.f + j*40.f);
            invaderY = (30.f + i*40.f);
            earthDestroyers.push_back(new invader(invaderX,invaderY,tipo)); 
            cout << invaderX << " " << invaderY << "\n";
        }
   }
   
    this->invadersDirection = 0;
    this->initBarriers(60,470);
    this->initBarriers(260,470);
    this->initBarriers(460,470);
    this->initBarriers(660,470);
       
   
   cout << earthDestroyers.size() << "\n";
   

}

   
int gameEngine::initSound( ){      
           
       if(!this->buffer->loadFromFile("sounds/shoot.wav")){
           return -1;
       }
       
       this->sound->setBuffer(*(this->buffer));
       
       return 0;
}

bool gameEngine::paused(){
        return this->pause;
}

void gameEngine::invadersShoot(){
    
    if(lastShoot == randomShootingTime){
        lastShoot = 0;
        bullet *invaderBullet = new bullet((this->earthDestroyers[earthDestroyers.size()-1]->getX() + 22), (this->earthDestroyers[earthDestroyers.size()-1]->getY()+2));
        invaderBullet->shootByInvader();
        bullets.push_back(invaderBullet);
    }
    else{
        lastShoot++;   
    }
}
   
void gameEngine::invadersCometoEarth(){
    
    
        if(this->invadersDirection == 0){  
            for(int i =0;i < earthDestroyers.size(); i++ )
                this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX()+10.f,this->earthDestroyers[i]->getY());   
            
            if(this->timesOneSide >= 33){ 
                for(int i =0;i < earthDestroyers.size(); i++ )
                    this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX(),this->earthDestroyers[i]->getY()+10.f); 
                
                this->invadersDirection = 1;
                this->timesOneSide = 0;               
            }
        }        
        else{
            for(int i =0;i < earthDestroyers.size(); i++ )
                this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX()-10.f,this->earthDestroyers[i]->getY());           
            if(this->timesOneSide == 33){ 
                for(int i =0;i < earthDestroyers.size(); i++ )
                    this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX(),this->earthDestroyers[i]->getY()+10.f);   
               
                this->invadersDirection = 0;
                this->timesOneSide = 0;                 
            }       
    } 
    this->timesOneSide++;

}
void gameEngine::runGame(){
    
    
      this->readInput();//reads keyboard and updates player position
      
    if(this->pause == true){
        return;
    }
    
  
    this->invadersCometoEarth();//spaceInvadersMoviment,this class works. But it is mainly an example on how the invaders could behave, again what will they be? a Matrix or a list?Both can be used in a for loop.
        //Add all the smartiness of the game here, shoots, space invaders
     this->moveBullets();
    this->invadersShoot();
     //Collision Detection
     this->collision();
    //Random creation of UFO    
}

player gameEngine::getPlayer(){
    return *(this->gamer);
}

std::vector<bullet*> gameEngine::getBullets(){
     return this->bullets;     
 }
 
 std::vector<barrier*> gameEngine::getBarriers(){
     return this->barriers;     
 }

std::vector<invader*> gameEngine::getInvaders(){
    return this->earthDestroyers;
    
}


 void gameEngine::shootSound( ){     
     this->sound->play();     
 }

void gameEngine::collision(){
    
    int distanceBulletInvader = -1;
    
     for(int j = 0; j < this->bullets.size();j++) {
        for(int b = 0; b < this->barriers.size();b++){
            
               if(isBulletInTheArea(*(this->bullets[j]), *(this->barriers[b]))){                       
                        barriers.erase(barriers.begin()+b);
                        //alsoDeleteBullets
                        bullets.erase(bullets.begin() + j);
                 break;                
               }
        }
        
        if(this->bullets[j]->getDirection() == -1 ){
            if(isBulletInTheArea(*(this->bullets[j]), *(this->gamer))){            
                    this->gamer->wasHit();
                    bullets.erase(bullets.begin() + j);                    
            }
            continue;//even if the bullet doesnt kill the bullet , it can not go to the check routine for the invaders, as it will kill them.
        }
        
        
        for(int i = 0; i < this->earthDestroyers.size();i++){
           if(!this->earthDestroyers[i]->isAlive()){
                earthDestroyers.erase(earthDestroyers.begin()+i);
                continue;
            }
            if(isBulletInTheArea(*(this->bullets[j]),*(this->earthDestroyers[i]))){
                        this->gamer->setScore(earthDestroyers[i]->getScore());
                             //earthDestroyers.erase(earthDestroyers.begin()+i);
                            //alsoDeleteBullets
                         bullets.erase(bullets.begin() + j);
                 break;
            }
            }
        
    }
}

bool gameEngine::isBulletInTheArea(bullet balas, barrier elBadBoys){
    
    if(balas.getX() < elBadBoys.getX() || balas.getY() < elBadBoys.getY())
        return false;
    
    float x = balas.getX() - elBadBoys.getX();
    float y = balas.getY() - elBadBoys.getY();
    float distance = sqrt(x*x+y*y);
        
    if(distance <= 5.f)
        return true;
    else
        return false;
}

bool gameEngine::isBulletInTheArea(bullet balas, invader elBadBoys){
    
    if(balas.getX() < elBadBoys.getX() || balas.getY() < elBadBoys.getY())
        return false;
    
    float x = balas.getX() - elBadBoys.getX();
    float y = balas.getY() - elBadBoys.getY();
    float distance = sqrt(x*x+y*y);
        
    if(distance <= 30.f)
        return true;
    else
        return false;
}

bool gameEngine::isBulletInTheArea(bullet balas, player elBadBoys){
    
    if( balas.getY() < 540.f)
        return false;
    
    float x = balas.getX() - elBadBoys.getX();
    float y = balas.getY() - elBadBoys.getY();
    float distance = sqrt(x*x+y*y);
        
    if(distance <= 30.f)
        return true;
    else
        return false;
}
    
void gameEngine::moveBullets(){
    
    for(int j = 0; j < bullets.size(); j++){
            if(bullets[j]->getDirection() == 1){
                    if ((bullets[j]->getY() - 10) <= 0){
                        bullets.erase(bullets.begin()+j);
                    }
                    else{
                    bullets[j]->setPosition(bullets[j]->getY() - 10);
                    }
            }
            else{
                    if ((bullets[j]->getY() + 10) <= 0){
                        bullets.erase(bullets.begin()+j);
                    }
                    else{
                        bullets[j]->setPosition(bullets[j]->getY() + 10);
                    }
            }
        }    
}

void gameEngine::readInput(){
    
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
             this->pause = !pause;
}

if(pause == true)
    return;//This way it wont allow the player to move

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
             this->gamer->setPosition(this->gamer->getX() - 20);
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->gamer->setPosition(this->gamer->getX() + 20);
}


if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
             bullets.push_back(new bullet((this->gamer->getX() + 22), this->gamer->getY()));
             this-> shootSound( );
             }
}

void gameEngine::initBarriers(int posx,int posy){
    
    int bX = posx;
    int bY = posy+10;
    
    int updateX,updateY;
    int pieces = 5;
    int growth = 1;
    //Barriers are generated from left to right, and down to up
    for(int i = 0; i < 9;i++){
        
         for(int j = 0; j < pieces; j++){
             
             updateX = bX+(i*10);
             updateY = bY-(j*10);
             barriers.push_back(new barrier(updateX, updateY));
             
         }
         if(i == pieces/2){
                growth = -1;
         }
         pieces = pieces+growth;
         
    }   
    
}

#endif
