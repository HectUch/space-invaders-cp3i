#ifndef GAMEENGINE_H
#include <SFML/Audio.hpp>
#include "ScreenGen.h"
#include "element.h"
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include "gameEngine.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <time.h>
#define GAMEENGINE_H

using namespace std::chrono;

gameEngine::gameEngine(){
    
    //Sound Initialization
    sound = new sf::Sound();
    buffer = new sf::SoundBuffer();    
    initSound( );
    screen = 0;
    option = 0;
    pause = false;
    exit = false;
    //Game logic initialization
   gamer = new player();
    level = 1;
    timeDelay = 0;

    this->initInvaders();
   
    
    this->initBarriers(60,470);
    this->initBarriers(260,470);
    this->initBarriers(460,470);
    this->initBarriers(660,470);      
   
   cout << earthDestroyers.size() << "\n";   

}

void gameEngine::initInvaders(){
   float invaderX = 40.f;
   float invaderY = 40.f;
   char tipo = 'C';
   randomShootingTime = 20;
   lastShoot = 0;
   timesOneSide = 0;
    
   this->invadersDirection = 0;   
    for(int i = 0;i < 5;i++)
   {
       if(i > 1 && i < 3)
           tipo = 'A';
       else if(i >= 3)
           tipo = 'B';
        for(int j = 0;j < 11;j++)
        {
            invaderX = (20.f + j*40.f);
            invaderY = (30.f + i*40.f);
            earthDestroyers.push_back(new invader(invaderX,invaderY,tipo)); 
            cout << invaderX << " " << invaderY <<  " " << tipo << "\n";
        }
   } 
}

bool gameEngine::exitGame(){
        return this->exit;
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
    
    
    int invader = earthDestroyers.size()-1;
    
    if(invader < 1)
        return;
    
    if(lastShoot == randomShootingTime){
        lastShoot = rand()%15;
        bullet *invaderBullet = new bullet((this->earthDestroyers[rand()%invader]->getX() + 22), (this->earthDestroyers[rand()%invader]->getY()+2));
        invaderBullet->shootByInvader();
        bullets.push_back(invaderBullet);
    }
    else{
        lastShoot++;   
    }
}

//void *gameEngine::invadersCometoEarth(void *arg){
    
    void gameEngine::invadersCometoEarth(){
    
    for(int jo = 0; jo < earthDestroyers.size(); jo++){
        if ((earthDestroyers[jo]->getX() == 760) && (this->invadersDirection == 0)){
            for(int i =0;i < earthDestroyers.size(); i++ ){
                    this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX(),this->earthDestroyers[i]->getY()+10.f);
            }
            invadersDirection = 1;
        }
        if ((earthDestroyers[jo]->getX() == 0) && (this->invadersDirection == 1)){
            for(int i =0;i < earthDestroyers.size(); i++ ){
                    this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX(),this->earthDestroyers[i]->getY()+10.f);
            }
            invadersDirection = 0;
        }
        
        
    }
    
    if(this->invadersDirection == 0){  
        for(int i =0;i < earthDestroyers.size(); i++ )
            this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX()+10.f,this->earthDestroyers[i]->getY());   
        } 
           
    if(this->invadersDirection == 1){  
        for(int i =0;i < earthDestroyers.size(); i++ )
            this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX()-10.f,this->earthDestroyers[i]->getY());   
        } 
            //if(this->timesOneSide >= 33){ 
                //for(int i =0;i < earthDestroyers.size(); i++ ){
                    //this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX(),this->earthDestroyers[i]->getY()+10.f); 
                //}
                //this->invadersDirection = 1;
                //this->timesOneSide = 0;               
            //}
                
            //for(int i =0;i < earthDestroyers.size(); i++ ){
                //this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX()-10.f,this->earthDestroyers[i]->getY());
            //}           
            //if(this->timesOneSide == 33){ 
                //for(int i =0;i < earthDestroyers.size(); i++ )
                    //this->earthDestroyers[i]->setPosition(this->earthDestroyers[i]->getX(),this->earthDestroyers[i]->getY()+10.f);   
               
                //this->invadersDirection = 0;
                //this->timesOneSide = 0;                 
            //}
    //this->timesOneSide++;
    
    ////return NULL;

}
void gameEngine::runGame(){
    
    //int joe = 0;
    
    //auto start = high_resolution_clock::now();
    
    
    this->readInput();//reads keyboard and updates player position    
     
    if(this->pause == true){
        return;
    } 
    
    if (clock() > timeDelay){
    this->invadersCometoEarth();
    timeDelay = clock() + 100000;
    timer = true;
    //spaceInvadersMoviment,this class works. But it is mainly an example on how the invaders could behave, again what will they be? a Matrix or a list?Both can be used in a for loop.
        //Add all the smartiness of the game here, shoots, space invaders
    }
    else{
        timer = false;
        }
     
     //pthread_create(&this->invadersCometoEarth, NULL, invadersCometoEarth, (void *)joe);
        
     this->moveBullets();
     this->invadersShoot();
     //Collision Detection
     this->collision();
    //Random creation of UFO
     if(earthDestroyers.size() == 0){
         this->initInvaders();
         level++;         
     }
     
     //auto stop = high_resolution_clock::now();
     
     //auto duration = duration_cast<microseconds> (stop - start);
     
     //cout << duration.count() << endl;
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

bool gameEngine::getTimer(){
    return this->timer;
}

 void gameEngine::shootSound( ){     
     this->sound->play();     
 }

void gameEngine::collision(){
    
    int distanceBulletInvader = -1;
    
    for(int i = 0; i < this->earthDestroyers.size();i++){
           if(!this->earthDestroyers[i]->isAlive()){
                earthDestroyers.erase(earthDestroyers.begin()+i);
                //earthDestroyers[i]->setType('F');
                continue;
            }
        }
    
     for(int j = 0; j < this->player_bullets.size();j++) {
        for(int b = 0; b < this->barriers.size();b++){
            
               if(isBulletInTheArea(*(this->player_bullets[j]), *(this->barriers[b]))){                       
                        barriers.erase(barriers.begin()+b);
                        //alsoDeleteBullets
                        player_bullets.erase(player_bullets.begin()+j);
                 break;                
               }
        }
        
        if(this->player_bullets[j]->getDirection() == -1 ){
            if(isBulletInTheArea(*(this->player_bullets[j]), *(this->gamer))){            
                    this->gamer->wasHit();
                    player_bullets.erase(player_bullets.begin() + j);                    
            }
            continue;//even if the bullet doesnt kill the bullet , it can not go to the check routine for the invaders, as it will kill them.
        }
        
        
        for(int i = 0; i < this->earthDestroyers.size();i++){
            if(isBulletInTheArea(*(this->player_bullets[j]),*(this->earthDestroyers[i]))){
                        this->gamer->setScore(earthDestroyers[i]->getScore());
                        earthDestroyers[i]->setType('F');
                             //earthDestroyers.erase(earthDestroyers.begin()+i);
                            //alsoDeleteBullets
                         player_bullets.erase(player_bullets.begin() + j);
                 break;
            }
            }
        
    }
    
    for(int j = 0; j < this->bullets.size();j++) {
        for(int b = 0; b < this->barriers.size();b++){
            
               if(isBulletInTheArea(*(this->bullets[j]), *(this->barriers[b]))){                       
                        barriers.erase(barriers.begin()+b);
                        //alsoDeleteBullets
                        bullets.erase(bullets.begin()+j);
                        break;                
               }
        }
        
        if(isBulletInTheArea(*(this->bullets[j]), *(this->gamer))){            
                this->gamer->wasHit();
                bullets.erase(bullets.begin() + j);                    
            }
            //even if the bullet doesnt kill the bullet , it can not go to the check routine for the invaders, as it will kill them.
        
    }
    
}

std::vector<bullet*> gameEngine::getPlayerBullets(){
     return this->player_bullets;     
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
                    if ((bullets[j]->getY() + 10) >= 600){
                        bullets.erase(bullets.begin()+j);
                    }
                    else{
                        bullets[j]->setPosition(bullets[j]->getY() + 1);
                    }
    }
    
    for(int j = 0; j < player_bullets.size(); j++){
                    if((player_bullets[j]->getY() - 10) <= 0){
                        player_bullets.erase(player_bullets.begin()+j);
                    }
                    else{
                    player_bullets[j]->setPosition(player_bullets[j]->getY() - 5);
                    }
    }
}    

int gameEngine::getScreen(){    
    return this->screen;  //Return  Main Menu = 0, Play Game = 1, Exit = 4, HighScore = 2 , About the Game = 3    
}

int gameEngine::getOption(){
     this->readInput();//reads keyboard
    return this->option; //Return  Main Menu = 0, Play Game = 1, Exit = 4, HighScore = 2 , About the Game = 3
    
}

void gameEngine::readInput(){

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
             this->exit = !exit;
}    

if(screen == 0){//Main Menu

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
             this->option--;
             if(option < 0)
                 option = 4;
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
             this->option++;
             if(option > 4)
                 option = 0;
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            //Return  Main Menu = 0, Play Game = 1, Exit = 4, HighScore = 2 , About the Game = 3
            if(option == 0)
                    this->screen++; //Screen = 1 is the game itself
            else    if(option == 1){
                //HighScore implementation
            }
            else    if(option == 3){
                //Creators Faces?
            }
            else {
                screen = 4;
                this->exit = !exit;
            }     
}
}


if(screen < 1)
    return;

if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ){
             this->pause = !pause;
}

if(pause == true)
    return;//This way it wont allow the player to move

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
             this->gamer->setPosition(this->gamer->getX() - 5);
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->gamer->setPosition(this->gamer->getX() + 5);
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
             if((player_bullets.size()<=3)&& shoot_state){
             player_bullets.push_back(new bullet((this->gamer->getX() + 22), this->gamer->getY()));
             this-> shootSound( );
             shoot_state = false;
         }
         }
else{
    
    shoot_state = true;
    
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
