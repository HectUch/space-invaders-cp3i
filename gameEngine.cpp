#ifndef GAMEENGINE_H
#include <SFML/Graphics.hpp>
#include "ScreenGen.h"
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include "gameEngine.h"
#include <vector>
#include <cmath>
#define GAMEENGINE_H

gameEngine::gameEngine(){
    
   gamer = new player();
   float invaderX = 40.f;
   float invaderY = 40.f;
   timesOneSide = 0;
   //this->earthDestroyers = new <vector>();
   //earthDestroyers = new std::array<invader*>(55);
   char tipo = 'C';
   
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
            invaderY = (20.f + i*40.f);
            earthDestroyers.push_back(new invader(invaderX,invaderY,tipo)); 
            cout << invaderX << " " << invaderY << "\n";
   }
   }

   
   cout << earthDestroyers.size() << "\n";
   
   //earthDestroyers = new invader(40.f,40.f,'C'); //creating the number of invaders we need? What is the best option push_pull list? vectors and pointers?
   //Yeah, Itiros = new bullet(40.f,40.f);
    this->invadersDirection = 0;
    
    barriers.push_back(new barrier(60, 430));
    barriers.push_back(new barrier(60, 440));
    barriers.push_back(new barrier(60, 450));
    barriers.push_back(new barrier(60, 460));
    barriers.push_back(new barrier(60, 470));
    barriers.push_back(new barrier(70, 420));
    barriers.push_back(new barrier(70, 430));
    barriers.push_back(new barrier(70, 440));
    barriers.push_back(new barrier(70, 450));
    barriers.push_back(new barrier(70, 460));
    barriers.push_back(new barrier(70, 470));
    barriers.push_back(new barrier(80, 410));
    barriers.push_back(new barrier(80, 420));
    barriers.push_back(new barrier(80, 430));
    barriers.push_back(new barrier(80, 440));
    barriers.push_back(new barrier(80, 450));
    barriers.push_back(new barrier(80, 460));
    barriers.push_back(new barrier(80, 470));
    barriers.push_back(new barrier(90, 400));
    barriers.push_back(new barrier(90, 410));
    barriers.push_back(new barrier(90, 420));
    barriers.push_back(new barrier(90, 430));
    barriers.push_back(new barrier(90, 440));
    barriers.push_back(new barrier(90, 450));
    barriers.push_back(new barrier(90, 460));
    barriers.push_back(new barrier(100, 390));
    barriers.push_back(new barrier(100, 400));
    barriers.push_back(new barrier(100, 410));
    barriers.push_back(new barrier(100, 420));
    barriers.push_back(new barrier(100, 430));
    barriers.push_back(new barrier(100, 440));
    barriers.push_back(new barrier(100, 450));
    barriers.push_back(new barrier(110, 400));
    barriers.push_back(new barrier(110, 410));
    barriers.push_back(new barrier(110, 420));
    barriers.push_back(new barrier(110, 430));
    barriers.push_back(new barrier(110, 440));
    barriers.push_back(new barrier(110, 450));
    barriers.push_back(new barrier(110, 460));
    barriers.push_back(new barrier(120, 410));
    barriers.push_back(new barrier(120, 420));
    barriers.push_back(new barrier(120, 430));
    barriers.push_back(new barrier(120, 440));
    barriers.push_back(new barrier(120, 450));
    barriers.push_back(new barrier(120, 460));
    barriers.push_back(new barrier(120, 470));
    barriers.push_back(new barrier(130, 420));
    barriers.push_back(new barrier(130, 430));
    barriers.push_back(new barrier(130, 440));
    barriers.push_back(new barrier(130, 450));
    barriers.push_back(new barrier(130, 460));
    barriers.push_back(new barrier(130, 470));
    barriers.push_back(new barrier(140, 430));
    barriers.push_back(new barrier(140, 440));
    barriers.push_back(new barrier(140, 450));
    barriers.push_back(new barrier(140, 460));
    barriers.push_back(new barrier(140, 470));
    
    barriers.push_back(new barrier(260, 430));
    barriers.push_back(new barrier(260, 440));
    barriers.push_back(new barrier(260, 450));
    barriers.push_back(new barrier(260, 460));
    barriers.push_back(new barrier(260, 470));
    barriers.push_back(new barrier(270, 420));
    barriers.push_back(new barrier(270, 430));
    barriers.push_back(new barrier(270, 440));
    barriers.push_back(new barrier(270, 450));
    barriers.push_back(new barrier(270, 460));
    barriers.push_back(new barrier(270, 470));
    barriers.push_back(new barrier(280, 410));
    barriers.push_back(new barrier(280, 420));
    barriers.push_back(new barrier(280, 430));
    barriers.push_back(new barrier(280, 440));
    barriers.push_back(new barrier(280, 450));
    barriers.push_back(new barrier(280, 460));
    barriers.push_back(new barrier(280, 470));
    barriers.push_back(new barrier(290, 400));
    barriers.push_back(new barrier(290, 410));
    barriers.push_back(new barrier(290, 420));
    barriers.push_back(new barrier(290, 430));
    barriers.push_back(new barrier(290, 440));
    barriers.push_back(new barrier(290, 450));
    barriers.push_back(new barrier(290, 460));
    barriers.push_back(new barrier(300, 390));
    barriers.push_back(new barrier(300, 400));
    barriers.push_back(new barrier(300, 410));
    barriers.push_back(new barrier(300, 420));
    barriers.push_back(new barrier(300, 430));
    barriers.push_back(new barrier(300, 440));
    barriers.push_back(new barrier(300, 450));
    barriers.push_back(new barrier(310, 400));
    barriers.push_back(new barrier(310, 410));
    barriers.push_back(new barrier(310, 420));
    barriers.push_back(new barrier(310, 430));
    barriers.push_back(new barrier(310, 440));
    barriers.push_back(new barrier(310, 450));
    barriers.push_back(new barrier(310, 460));
    barriers.push_back(new barrier(320, 410));
    barriers.push_back(new barrier(320, 420));
    barriers.push_back(new barrier(320, 430));
    barriers.push_back(new barrier(320, 440));
    barriers.push_back(new barrier(320, 450));
    barriers.push_back(new barrier(320, 460));
    barriers.push_back(new barrier(320, 470));
    barriers.push_back(new barrier(330, 420));
    barriers.push_back(new barrier(330, 430));
    barriers.push_back(new barrier(330, 440));
    barriers.push_back(new barrier(330, 450));
    barriers.push_back(new barrier(330, 460));
    barriers.push_back(new barrier(330, 470));
    barriers.push_back(new barrier(340, 430));
    barriers.push_back(new barrier(340, 440));
    barriers.push_back(new barrier(340, 450));
    barriers.push_back(new barrier(340, 460));
    barriers.push_back(new barrier(340, 470));
    
    barriers.push_back(new barrier(460, 430));
    barriers.push_back(new barrier(460, 440));
    barriers.push_back(new barrier(460, 450));
    barriers.push_back(new barrier(460, 460));
    barriers.push_back(new barrier(460, 470));
    barriers.push_back(new barrier(470, 420));
    barriers.push_back(new barrier(470, 430));
    barriers.push_back(new barrier(470, 440));
    barriers.push_back(new barrier(470, 450));
    barriers.push_back(new barrier(470, 460));
    barriers.push_back(new barrier(470, 470));
    barriers.push_back(new barrier(480, 410));
    barriers.push_back(new barrier(480, 420));
    barriers.push_back(new barrier(480, 430));
    barriers.push_back(new barrier(480, 440));
    barriers.push_back(new barrier(480, 450));
    barriers.push_back(new barrier(480, 460));
    barriers.push_back(new barrier(480, 470));
    barriers.push_back(new barrier(490, 400));
    barriers.push_back(new barrier(490, 410));
    barriers.push_back(new barrier(490, 420));
    barriers.push_back(new barrier(490, 430));
    barriers.push_back(new barrier(490, 440));
    barriers.push_back(new barrier(490, 450));
    barriers.push_back(new barrier(490, 460));
    barriers.push_back(new barrier(500, 390));
    barriers.push_back(new barrier(500, 400));
    barriers.push_back(new barrier(500, 410));
    barriers.push_back(new barrier(500, 420));
    barriers.push_back(new barrier(500, 430));
    barriers.push_back(new barrier(500, 440));
    barriers.push_back(new barrier(500, 450));
    barriers.push_back(new barrier(510, 400));
    barriers.push_back(new barrier(510, 410));
    barriers.push_back(new barrier(510, 420));
    barriers.push_back(new barrier(510, 430));
    barriers.push_back(new barrier(510, 440));
    barriers.push_back(new barrier(510, 450));
    barriers.push_back(new barrier(510, 460));
    barriers.push_back(new barrier(520, 410));
    barriers.push_back(new barrier(520, 420));
    barriers.push_back(new barrier(520, 430));
    barriers.push_back(new barrier(520, 440));
    barriers.push_back(new barrier(520, 450));
    barriers.push_back(new barrier(520, 460));
    barriers.push_back(new barrier(520, 470));
    barriers.push_back(new barrier(530, 420));
    barriers.push_back(new barrier(530, 430));
    barriers.push_back(new barrier(530, 440));
    barriers.push_back(new barrier(530, 450));
    barriers.push_back(new barrier(530, 460));
    barriers.push_back(new barrier(530, 470));
    barriers.push_back(new barrier(540, 430));
    barriers.push_back(new barrier(540, 440));
    barriers.push_back(new barrier(540, 450));
    barriers.push_back(new barrier(540, 460));
    barriers.push_back(new barrier(540, 470));
    
    barriers.push_back(new barrier(660, 430));
    barriers.push_back(new barrier(660, 440));
    barriers.push_back(new barrier(660, 450));
    barriers.push_back(new barrier(660, 460));
    barriers.push_back(new barrier(660, 470));
    barriers.push_back(new barrier(670, 420));
    barriers.push_back(new barrier(670, 430));
    barriers.push_back(new barrier(670, 440));
    barriers.push_back(new barrier(670, 450));
    barriers.push_back(new barrier(670, 460));
    barriers.push_back(new barrier(670, 470));
    barriers.push_back(new barrier(680, 410));
    barriers.push_back(new barrier(680, 420));
    barriers.push_back(new barrier(680, 430));
    barriers.push_back(new barrier(680, 440));
    barriers.push_back(new barrier(680, 450));
    barriers.push_back(new barrier(680, 460));
    barriers.push_back(new barrier(680, 470));
    barriers.push_back(new barrier(690, 400));
    barriers.push_back(new barrier(690, 410));
    barriers.push_back(new barrier(690, 420));
    barriers.push_back(new barrier(690, 430));
    barriers.push_back(new barrier(690, 440));
    barriers.push_back(new barrier(690, 450));
    barriers.push_back(new barrier(690, 460));
    barriers.push_back(new barrier(700, 390));
    barriers.push_back(new barrier(700, 400));
    barriers.push_back(new barrier(700, 410));
    barriers.push_back(new barrier(700, 420));
    barriers.push_back(new barrier(700, 430));
    barriers.push_back(new barrier(700, 440));
    barriers.push_back(new barrier(700, 450));
    barriers.push_back(new barrier(710, 400));
    barriers.push_back(new barrier(710, 410));
    barriers.push_back(new barrier(710, 420));
    barriers.push_back(new barrier(710, 430));
    barriers.push_back(new barrier(710, 440));
    barriers.push_back(new barrier(710, 450));
    barriers.push_back(new barrier(710, 460));
    barriers.push_back(new barrier(720, 410));
    barriers.push_back(new barrier(720, 420));
    barriers.push_back(new barrier(720, 430));
    barriers.push_back(new barrier(720, 440));
    barriers.push_back(new barrier(720, 450));
    barriers.push_back(new barrier(720, 460));
    barriers.push_back(new barrier(720, 470));
    barriers.push_back(new barrier(730, 420));
    barriers.push_back(new barrier(730, 430));
    barriers.push_back(new barrier(730, 440));
    barriers.push_back(new barrier(730, 450));
    barriers.push_back(new barrier(730, 460));
    barriers.push_back(new barrier(730, 470));
    barriers.push_back(new barrier(740, 430));
    barriers.push_back(new barrier(740, 440));
    barriers.push_back(new barrier(740, 450));
    barriers.push_back(new barrier(740, 460));
    barriers.push_back(new barrier(740, 470));
       
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
    this->invadersCometoEarth();//spaceInvadersMoviment,this class works. But it is mainly an example on how the invaders could behave, again what will they be? a Matrix or a list?Both can be used in a for loop.
    //Add all the smartiness of the game here, shoots, space invaders
     this->moveBullets();
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

//void gameEngine::collision(){
    //int distanceBulletInvader = -1;
    
    //for(int j = 0; j < this->bullets.size();j++) 
        //for(int i = 0; i < this->earthDestroyers.size();i++)
               //if(isBulletInTheArea(*(this->bullets[j]),*(this->earthDestroyers[i]))){
                 //this->earthDestroyers[i]->getHit();
                 //alsoDeleteBullets
                //this->bullets[j]->setPosition(-10.f);
                 //break;
            //}   
//}

void gameEngine::collision(){
    int distanceBulletInvader = -1;
    
    for(int n = 0; n < this->bullets.size();n++) {
        for(int b = 0; b < this->barriers.size();b++){
               if((bullets[n]->getX() >= barriers[b]->getX()) && (bullets[n]->getX() <= (barriers[b]->getX() + 5))){
                   if(bullets[n]->getY() == barriers[b]->getY()){
                 barriers.erase(barriers.begin()+b);
                 //alsoDeleteBullets
                bullets.erase(bullets.begin() + n);
                 break;
                    }  
               }
        }
    }
    
    for(int j = 0; j < this->bullets.size();j++) {
        for(int i = 0; i < this->earthDestroyers.size();i++){
               if((bullets[j]->getX() >= earthDestroyers[i]->getX()) && (bullets[j]->getX() <= (earthDestroyers[i]->getX() + 20))){
                   if((bullets[j]->getY() <= earthDestroyers[i]->getY()) && (bullets[j]->getY() >= (earthDestroyers[i]->getY() - 20))){
                 earthDestroyers.erase(earthDestroyers.begin()+i);
                 //alsoDeleteBullets
                bullets.erase(bullets.begin() + j);
                 break;
                    }
               }
        }
    }
    
    
}

bool gameEngine::isBulletInTheArea(bullet balas, invader elBadBoys){
    
    if(balas.getX() < elBadBoys.getX() || balas.getY() < elBadBoys.getY())
        return false;
    
    float x = balas.getX() - elBadBoys.getX();
    float y = balas.getY() - elBadBoys.getY();
    float distance = sqrt(x*x+y*y);
        
    if(distance <= 3.f)
        return true;
    else
        return false;
}
    
void gameEngine::moveBullets(){
    
    for(int j = 0; j < bullets.size(); j++){
                    if ((bullets[j]->getY() - 10) <= 0){
                        bullets.erase(bullets.begin()+j);
                    }
                    else{
                    bullets[j]->setPosition(bullets[j]->getY() - 10);
                    }
        }
    
}
 


void gameEngine::readInput(){
    

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
              // left key is pressed: move our character
             //playerSprite.move(-20.f, 0.f);
             this->gamer->setPosition(this->gamer->getX() - 20);
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
              // left key is pressed: move our character
             //playerSprite.move(20.f, 0.f);
            this->gamer->setPosition(this->gamer->getX() + 20);
}


if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
              // left key is pressed: move our character
             //playerSprite.move(-20.f, 0.f);
             //bullet bullet1(this->gamer->getX(), this->gamer->getY());
             bullets.push_back(new bullet((this->gamer->getX() + 22), this->gamer->getY()));
             }
}

#endif
