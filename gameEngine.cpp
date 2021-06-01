#ifndef GAMEENGINE_H
#include <SFML/Graphics.hpp>
#include "ScreenGen.h"
#include "player.h"
#include "bullet.h"
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

std::vector<invader*> gameEngine::getInvaders(){
    return this->earthDestroyers;
    
}

void gameEngine::collision(){
    int distanceBulletInvader = -1;
    
    for(int j = 0; j < this->bullets.size();j++) 
        for(int i = 0; i < this->earthDestroyers.size();i++)
               if(isBulletInTheArea(*(this->bullets[j]),*(this->earthDestroyers[i]))){
                 this->earthDestroyers[i]->getHit();
                 //alsoDeleteBullets
                this->bullets[j]->setPosition(-10.f);
                 break;
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
             bullets.push_back(new bullet(this->gamer->getX(), this->gamer->getY()));
             }
}

#endif
