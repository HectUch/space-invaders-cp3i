#ifndef GAMEENGINE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
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
#include <fstream>
#include <sstream>

#define GAMEENGINE_H

using namespace std::chrono;
using namespace std;

gameEngine::gameEngine(){
    
    //Sound Initialization
    sound = new sf::Sound();
    buffer = new sf::SoundBuffer();    
    initSound( );
    screen = 0;
    option = 0;
   
    exit = false;
    //Game logic initialization
    restartGame();

}

void gameEngine::restartGame(){
    
    exit = false;
    //Game logic initialization
    pause = false;
    gamer = new player();
    level = 1;
    timeDelay_invader = 0;
    timeDelay_bullet = 0;
    isItTimeforASurprise = 0;
    randomShowUp = rand()%120;
    levelUpWait = 3000;
    levelSplashCount =0;
    
    //Initialization for the HighScore system
    first = 'A';
    second = 'A';
    third = 'A';
    letter = 0;
    
    this->initInvaders();    
    this->player_bullets.clear();
    this->bullets.clear();
    
    this->initBarriers(60,520);
    this->initBarriers(260,520);
    this->initBarriers(460,520);
    this->initBarriers(660,520);      
   
   cout << earthDestroyers.size() << "\n";  
}

void gameEngine::writeScore(std::string score){
        ofstream scores("highscores.txt", std::ios::in | std::ios::out |std::ios::ate);
        scores << score << endl;
        scores.close();
}

void gameEngine::fetchScore(){
        
        ifstream scores("highscores.txt", std::ios::in);
        
        if(!scores)
            return;
        
        string playerName,line;
        int score = 0;        
               
        while(getline(scores,line)){
            istringstream is(line);
            
            is >> playerName;
            is >> score;
            
            if(score >= scoreFirst){
                
                this->pScoreThird = pScoreSecond;
                this->pScoreSecond = pScoreFirst;
                this->pScoreFirst = playerName;
                this->scoreThird = scoreSecond;
                this->scoreSecond = scoreFirst;
                this->scoreFirst = score;
                                   
            }            
        }                
        scores.close();
}

string gameEngine::getPosScore(int pos){
        
    if (pos == 1){
        return (pScoreFirst  + " " + to_string(scoreFirst));
    }
    else if(pos == 2){
        return (pScoreSecond  + " " + to_string(scoreSecond));
    }
    else if(pos == 3){
        return (pScoreThird + " " + to_string(scoreThird));
    }
    else{
        return "";
    }
}

string gameEngine::getCharPos(){

    string a(1,first);
    string b(1,second);
    string c(1,third);

    return a+b+c;
}


invader gameEngine::getUFO(){
    
    return *UFO;
    
}

void gameEngine::initInvaders(){
    
   float iX = 20.f;
   float iY = 60.f;
   float invaderX = 20.f;
   float invaderY = 30.f;
   char tipo = 'C';
   randomShootingTime = 20;
   lastShoot = 0;
   timesOneSide = 0;
   int points = 100;
   earthDestroyers.clear();
   earthDestroyersShooters.clear();
   
   UFO = new invader(800.f,35.f,'U');
   UFO->recruitToWar(rand()%1000,'U');
   
   
   this->invadersDirection = 0;   
    for(int i = 4;i >= 0;i--)
   {
       
       if(i > 1 && i < 3){
           tipo = 'A';
           points = 200;
       }
       else if(i >= 3){
           tipo = 'B';
           points = 300;
       }
        for(int j = 0;j < 11;j++)
        {
            invaderX = (iX + j*40.f);
            invaderY = (iY + i*40.f);
            invader *alien = new invader(invaderX,invaderY,tipo);
            alien->recruitToWar(points*level,tipo);
            earthDestroyers.push_back(alien); 
            
            if(i == 4)
                earthDestroyersShooters.push_back(alien);    
            
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
    
    int invader = earthDestroyersShooters.size()-1;
    
    if(invader < 1)
        return;
    
    if(lastShoot == randomShootingTime){
        lastShoot = rand()%11;
        bullet *invaderBullet = new bullet((earthDestroyersShooters[rand()%11]->getX() + 11), (earthDestroyersShooters[rand()%11]->getY()+11));
        invaderBullet->shootByInvader();
        bullets.push_back(invaderBullet);
        //cout <<  invader << "\n";        
    }
    else{
        lastShoot++;   
    }
}

void gameEngine::invadersCometoEarth(){
    
    int maxY = 450;
    
    if(earthDestroyers[earthDestroyers.size()-1]->getY() >= maxY){
        screen = 5;
        pause = true;
    }
    
     if(UFO->getX() >= -50){
        this->UFO->setPosition(UFO->getX()-15.f,UFO->getY());        
    }
    else{        
        isItTimeforASurprise++;
        if(randomShowUp == isItTimeforASurprise){            
            this->UFO->setPosition(800.f,30.f);
            this->UFO->recruitToWar(1,'U');
            isItTimeforASurprise = 0;
            randomShowUp = rand()%150;
        }
    }
    
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
}

void gameEngine::runGame(){
    
    //int joe = 0;    
    //auto start = high_resolution_clock::now();    
    this->readInput();//reads keyboard and updates player position    
    
    if(this->screen == 6){
        levelSplashCount++;
    } 
    
    if( levelUpWait ==  levelSplashCount){
        levelSplashCount = 0;
        screen =1;
        pause = false;
    }
    
   
     if(this->pause == true || this->screen != 1){
        return;
    } 
    
     if (clock() > timeDelay_invader){
    
        this->invadersCometoEarth();
        timeDelay_invader = clock() + 100000;
        timer = true;
        //spaceInvadersMoviment,this class works. But it is mainly an example on how the invaders could behave, again what will they be? a Matrix or a list?Both can be used in a for loop.
        //Add all the smartiness of the game here, shoots, space invaders
    }
    else
    {
        timer = false;
    }
        
    if (clock() > timeDelay_bullet){
             
    this->invadersShoot();
    timeDelay_bullet =clock() + 10000;
    //spaceInvadersMoviment,this class works. But it is mainly an example on how the invaders could behave, again what will they be? a Matrix or a list?Both can be used in a for loop.
        //Add all the smartiness of the game here, shoots, space invaders
    }
          this->moveBullets();
     //pthread_create(&this->invadersCometoEarth, NULL, invadersCometoEarth, (void *)joe);          
          this->collision();
     
    //Random creation of UFO
    this->checkLevelStatus();
}

void gameEngine::checkLevelStatus(){
         if(this->gamer->getLives() == 0){
            //screen = 5;
            pause = true;
        }
        if(earthDestroyers.size() == 0){
            level++;
            //Show Level Screen Here
            levelUpWait = 1000;
            levelSplashCount =0;
            screen = 6;
            pause = true;
            //keep on the game
            this->initInvaders();          
        }
}

int gameEngine::getLevel(){
 
    return level;
    
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
        
       for(int i = 0; i < this->earthDestroyersShooters.size();i++){
           if(!this->earthDestroyersShooters[i]->isAlive()){
                earthDestroyersShooters.erase(earthDestroyersShooters.begin()+i);
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
    
    for(int i = 0; i < this->bullets.size();i++){
        if(isBulletInTheArea(*(this->bullets[i]), *(this->player_bullets[j]))){
            player_bullets.erase(player_bullets.begin()+j);
            bullets.erase(bullets.begin()+j);
        }          
    }
    
    
    if(isBulletInTheArea(*(this->player_bullets[j]),*UFO)){
        this->UFO->setPosition(-50.f,40.f);
        this->gamer->setScore(UFO->getScore());
    }
        
    for(int i = 0; i < this->earthDestroyersShooters.size();i++){
            if(isBulletInTheArea(*(this->player_bullets[j]),*(this->earthDestroyersShooters[i]))){
                      for(int p = (earthDestroyers.size() -1); p > 0; --p){
                                if ((earthDestroyers[p]->getX() == earthDestroyersShooters[i]->getX()) && (earthDestroyers[p]->getY() < earthDestroyersShooters[i]->getY()) ){
                                      earthDestroyersShooters[i] = earthDestroyers[p];
                                      
                                       break;
                                }
                      }
            }
    }
    
        
   for(int i = this->earthDestroyers.size()-1; i >= 0 ;i--){

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
    
    if(balas.getX()+1 < elBadBoys.getX() || balas.getY()+2 < elBadBoys.getY())
        return false;
    
    float x = balas.getX() - elBadBoys.getX();
    float y = balas.getY() - elBadBoys.getY();
    float distance = sqrt(x*x+y*y);
        
    if(distance <= 7.5f)
        return true;
    else
        return false;
}

bool gameEngine::isBulletInTheArea(bullet balas, bullet elBadBoys){
    
    /*if(balas.getX() < elBadBoys.getX() || balas.getY() < elBadBoys.getY())
        return false;*/
    
    float x = balas.getX() - elBadBoys.getX();
    float y = balas.getY() - elBadBoys.getY();
    float distance = sqrt(x*x+y*y);
        
    if(distance <= 3.f)
        return true;
    else
        return false;
}

bool gameEngine::isBulletInTheArea(bullet balas, invader elBadBoys){
    
    if(balas.getX()+1 < elBadBoys.getX() || balas.getY() < elBadBoys.getY())
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
    if(balas.getX()+1 < elBadBoys.getX() || balas.getY()+2 < elBadBoys.getY())
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
    return this->screen;  //Return  Main Menu = 0, Play Game = 1, Exit = 4, HighScore = 2 , About the Game = 3,gameOver  = 5   
}

int gameEngine::getOption(){
    //this->readInput();//reads keyboard
    return this->option; //Return  Main Menu = 0, Play Game = 1, Exit = 4, HighScore = 2 , About the Game = 3    
}

void gameEngine::readInput(){

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
             this->exit = !exit;
}    


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                this->option--;
                if(option < 0)
                    option = 4;
                
                if(letter == 0){
                    if(first == 'Z'){
                        first = 'A';
                    }
                    else
                        this->first++;                    
                }
                if(letter == 1){
                    if(second == 'Z'){
                        second = 'A';
                    }
                    else
                        this->second++;                    
                }
                if(letter == 2){
                    if(third == 'Z'){
                        third = 'A';
                    }
                    else
                        this->third++;                    
                }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                 sf::sleep(sf::milliseconds(100));
                this->option++;
                if(option > 4)
                    option = 0;
                
                if(letter == 0){
                    if(first == 'A'){
                        first = 'Z';
                    }
                    else
                        this->first--;                    
                }
                if(letter == 1){
                    if(second == 'A'){
                        second = 'Z';
                    }
                    else
                        this->second--;                    
                }
                if(letter == 2){
                    if(third == 'A'){
                        third = 'Z';
                    }
                    else
                        this->third--;                    
                }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                if(screen == 0){
                //Return  Main Menu = 0, Play Game = 1, Exit = 4, HighScore = 2 , About the Game = 3 , Game over Screen = 5
                        if(option == 0){
                            //this->screen++; //Screen = 1 is the game itself
                            levelUpWait = 750;
                            levelSplashCount =0;
                            screen = 6;
                            pause = true;
                        }       
                        else    if(option == 1){
                            //HighScore implementation
                            this->fetchScore();
                            option = 0;
                            screen = 2; 
                            sf::sleep(sf::milliseconds(100));
                        }
                        else    if(option == 2){
                            screen = 3;
                            sf::sleep(sf::milliseconds(100));
                        }
                        else {
                            screen = 4;
                            this->exit = !exit;
                        }                        
                    }
                    else if(screen == 1 && pause == true){
                        cout << "My letter is : " << letter << endl;
                        if(letter == 3){
                            string save = this->getCharPos()+ " " + to_string(this->gamer->getScore());
                            this->writeScore(save);
                            letter = 0;
                           screen = 5;   
                           pause = true;
                           sf::sleep(sf::milliseconds(100));
                        }
                        else{
                                letter++;
                        }
                    }
                    else if(screen == 2 || screen == 3){
                         
                        screen = 0;
                    }
                    else if(screen == 5){
                      sf::sleep(sf::milliseconds(100));      
                        if(option%2 == 0){
                                this->screen = 1; //Screen = 1 is the game itself
                                this->restartGame();
                        }                                    
                        else    if(option%2 == 1){
                                screen = 4;
                                this->exit = !exit;               
                        }
                }
    }


if(screen != 1)
    return;

if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ){//&& this->gamer->getLives() > 0 ){
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
    int bY = posy+20;    
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
