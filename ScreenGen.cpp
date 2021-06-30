#ifndef SCREENGEN_H
#include "ScreenGen.h"
#include "element.h"
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#define SCREENGEN_H

using namespace std;

ScreenGen::ScreenGen(sf::RenderWindow &window){    
        animation = 1;
        this->LoadText();   
        this->initAll();
        menu = 1;
}

void ScreenGen::initPlayer(player elPapitoSavior){   
    //this->gamer = elPapitoSavior;
    this->initSprites(playerSprite,'P');
    this->playerSprite.setPosition(elPapitoSavior.getX(),elPapitoSavior.getY());
    //this->animation = 1;
    scoreTextstring = "Score : < " + to_string(elPapitoSavior.getScore()) + " >";
    scoreText.setPosition(2.f,10.f);   
    scoreText.setString(scoreTextstring);     
}


void ScreenGen::initInvaders(sf::RenderWindow &window,std::vector<invader*> EarthDestroyers){    
    
    for(int i =0;i < EarthDestroyers.size(); i++ ){
       //if(!EarthDestroyers[i]->isAlive()){
            //continue;
        //}
        
        this->initSprites(invadersSprite,EarthDestroyers[i]->getType());   
        this->invadersSprite.setPosition(EarthDestroyers[i]->getX(),EarthDestroyers[i]->getY());    
        window.draw(invadersSprite);
    }    
}

void ScreenGen::initAll(){
    this->LoadTexture();
    delayTime = sf::milliseconds(100);
    this->initSprites(lifeSprite,'P');
   
}

  void ScreenGen::splashScreen(sf::RenderWindow &window){
      int color = 255;
      window.clear();
      cout << "I am here\n";
      for(int i = 0; i < 50; i++){
           
            gameOvert.setFont(font);
            gameOvert.setString("The C++ Jongens  Presents : ");
            gameOvert.setCharacterSize(35);
            gameOvert.setFillColor(sf::Color(color,color,color));
            gameOvert.setPosition(100.f,250.f);            
            
            window.draw(gameOvert);
            color = color - 25*i;          

        window.display();  
        this->delay();
       
      }
      
  }
  
void ScreenGen::MainMenu(sf::RenderWindow &window,int option){
            
            float optie = option +0.0f;
            window.clear();
            gameOvert.setFont(font);
            gameOvert.setString("Enschede Invaders ");
            gameOvert.setCharacterSize(35);
            gameOvert.setFillColor(sf::Color::White);
            gameOvert.setPosition(190.f,180.f);             
            window.draw(gameOvert);
            
            //Not Cool!
           /*gameOvert.setFont(font);
            gameOvert.setString(">");
            gameOvert.setCharacterSize(30);
            gameOvert.setFillColor(sf::Color::White);
            gameOvert.setPosition(290.f,270.f+optie*10.f);             
            window.draw(gameOvert);*/
           

            if(option == 0){
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(250.f,270.f);
                window.draw(invadersSprite);
                this->invadersSprite.setPosition(470.f,270.f);
                window.draw(invadersSprite);            
            }
            else if(option == 1){
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(250.f,310.f);
                window.draw(invadersSprite);
                this->invadersSprite.setPosition(470.f,310.f);
                window.draw(invadersSprite);
            }
            else if(option == 2){
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(205.f,350.f);
                window.draw(invadersSprite);
                this->invadersSprite.setPosition(525.f,350.f);
                window.draw(invadersSprite);
            }
            else{
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(320.f,390.f);
                window.draw(invadersSprite);
                this->invadersSprite.setPosition(430.f,390.f);
                window.draw(invadersSprite);
            }
            
            gameOvert.setFont(font);
            gameOvert.setString("Start Game ");
            gameOvert.setCharacterSize(25);
            gameOvert.setFillColor(sf::Color::White);
            gameOvert.setPosition(300.f,270.f);             
            window.draw(gameOvert);
      
            
            gameOvert.setFont(font);
            gameOvert.setString("High-Score ");
            gameOvert.setCharacterSize(25);
            gameOvert.setFillColor(sf::Color::White);
            gameOvert.setPosition(300.f,310.f);             
            window.draw(gameOvert);
            
            gameOvert.setFont(font);
            gameOvert.setString("About the Game");
            gameOvert.setCharacterSize(25);
            gameOvert.setFillColor(sf::Color::White);
            gameOvert.setPosition(265.f,350.f);             
            window.draw(gameOvert);
           
            gameOvert.setFont(font);
            gameOvert.setString("Exit ");
            gameOvert.setCharacterSize(25);
            gameOvert.setFillColor(sf::Color::White);
            gameOvert.setPosition(360.f,390.f);             
            window.draw(gameOvert);
            window.display();  
            this->Animate();
            this->delay();        
    
}



void ScreenGen::initSprites(sf::Sprite &sprite,char type){ 
    
    if(type == 'P'){
        sprite.setTexture(texturePlayer);
        sprite.setScale(sf::Vector2f(0.09f, 0.09f));
        return;
    }    
    if(type == 'Q'){
        sprite.setTexture(textureProjectile);
        sprite.setTextureRect(sf::IntRect(0, 0, 3, 7));
        sprite.setScale(sf::Vector2f(2, 2));
        return;        
    }
     if(type == 'F'){
        //this->LoadTexture();
        sprite.setTexture(textureExplosion);
        sprite.setTextureRect(sf::IntRect(0, 0, 160, 100));
        sprite.setScale(sf::Vector2f(0.3f, 0.3f));
        //cout << "HITF/n";
        sprite.setColor(sf::Color(255,255, 255)); // Rood./
        //sprite.setScale(sf::Vector2f(2, 2));
        return;        
    }      
   sprite.setTexture(texture);   
   sprite.setTextureRect(this->catchTextureByType(type,this->animation));
   sprite.setColor(sf::Color(0,255, 0)); // Rood./
   sprite.setScale(sf::Vector2f(0.3f, 0.3f)); // absolute scale factor
}

sf::IntRect ScreenGen::catchTextureByType(char type,int animation){
    if(type == 'U')
        return sf::IntRect(0, 0, 160, 100);//UFO
    else if((type == 'C') && animation == 1)
        return sf::IntRect(160, 0, 120, 100); //Crab 1
     else if((type == 'C') && animation == 2)
        return sf::IntRect(280, 0, 120, 100);//Crab 2
    else if((type == 'A') && animation == 1)
        return sf::IntRect(0, 100, 120, 100); //Polvo 1
     else if((type == 'A') && animation == 2)
        return sf::IntRect(120, 100, 120, 100);//Polvo 2
    else if((type == 'B') && animation == 1)
        return sf::IntRect(240, 100, 90, 100); //Barata 1
     else if((type == 'B') && animation == 2)
        return sf::IntRect(320, 100, 90, 100);//Barata 2
    else if((type == 'B') && animation == 2)
        return sf::IntRect(320, 100, 90, 100);//Barata 2
    else
        return sf::IntRect(780,275, 300, 300);//Explosion
}

void ScreenGen::updateLives(sf::RenderWindow &window,player gamer){
    
    shipsText.setFont(font);
    shipsText.setString("Ships : ");
    shipsText.setCharacterSize(15);
    shipsText.setFillColor(sf::Color::White);
    shipsText.setPosition(630.f,12.f);     
    if(gamer.getLives() == 0)return; 
    
    else{
        int lifes=gamer.getLives();
        float point=600.f;
        for(int i = 0; i < lifes;i++){
                point =700.0+30*i;
                lifeSprite.setPosition(point,2.f);
                lifeSprite.setScale(sf::Vector2f(0.06f, 0.06f)); 
                window.draw(lifeSprite);
        }
    }    
}

void ScreenGen::LoadTexture(){ 
     if (!texture.loadFromFile("images/allInvaders.png"))
    {
    // error...
        cout << "Could not load texture/n";
    }
   if (!textureExplosion.loadFromFile("images/explosion.png"))
    {
    // error...
    cout << "Could not load texture Explosion/n";
    }
    if (!texturePlayer.loadFromFile("images/player.png"))
    {
    // error...
        cout << "Could not load texture Player/n";
    }
    if (!textureProjectile.loadFromFile("images/projectile.png"))
    {
    // error...
    }    
}

void ScreenGen::LoadText(){
 
    if(!font.loadFromFile("fonts/space_invaders.ttf")){
        //Error...
    }

    scoreText.setFont(font);
    scoreText.setString("Score : < 0 >");
    scoreText.setCharacterSize(15);
    scoreText.setPosition(2.f,10.f);    
    scoreText.setFillColor(sf::Color::White);    
    

}

void ScreenGen::gameOver(sf::RenderWindow &window,player gamer){
    
    gameOvert.setFont(font);
    gameOvert.setString("GAME OVER");
   gameOvert.setCharacterSize(35);
    gameOvert.setFillColor(sf::Color::White);
    gameOvert.setPosition(300.f,250.f);
    
    
    window.draw(playerSprite);
    updateLives(window,gamer);         
    window.draw(scoreText);
    window.draw(gameOvert);
    
    gameOvert.setFont(font);
    gameOvert.setString("> RESTART");
    gameOvert.setCharacterSize(25);
    gameOvert.setFillColor(sf::Color::White);
    gameOvert.setPosition(350.f,300.f);
    
    window.draw(gameOvert);  
    
    
}

void ScreenGen::Animate(){
    
    if(this->animation == 1){
        this->animation = 2;}
    else{
        this->animation =1;}
    
}

void ScreenGen::playing(sf::RenderWindow &window,player gamer){
      
        
        window.draw(playerSprite);
        updateLives(window,gamer);         
        window.draw(scoreText);
        window.draw(shipsText);       
        
        //gamer.wasHit();
}

sf::Texture ScreenGen::getTexture(){
    return this->texture;
}

void ScreenGen::initBullets(sf::RenderWindow &window, std::vector<bullet*> bulletss1){
    
this->LoadTexture();
    
for(int n = 0; n < bulletss1.size(); n++){
            sf::Sprite poep;
            //this->LoadTexture();
            this->initSprites(poep,'Q');
            //bulletsprite1.setTextureRect(this->catchTextureByType('C',2));//Crab2
            poep.setPosition(bulletss1[n]->getX(),bulletss1[n]->getY());
            poep.setColor(sf::Color(255,0, 255)); // Rood./
            //bulletsprite1.setScale(sf::Vector2f(0.3f, 0.3f)); // absolute scale factor
            window.draw(poep);
}  
}

void ScreenGen::initBarriers(sf::RenderWindow &window, std::vector<barrier*> barrierss){
    
for(int l = 0; l < barrierss.size(); l++){
            sf::RectangleShape rectangle(sf::Vector2f(10.f, 10.f));
            rectangle.setPosition(barrierss[l]->getX(),barrierss[l]->getY());
            rectangle.setFillColor(sf::Color(0,255,0)); // Rood./
             window.draw(rectangle);
}           
   
}

void ScreenGen::isPaused(sf::RenderWindow &window,player gamer){
    
    gameOvert.setFont(font);
    gameOvert.setString("PAUSED");
    gameOvert.setCharacterSize(35);
    gameOvert.setFillColor(sf::Color::White);
    gameOvert.setPosition(300.f,250.f);
    window.draw(scoreText);
    window.draw(gameOvert);
    window.draw(playerSprite);
    updateLives(window,gamer);    
    
}


void ScreenGen::drawGame(sf::RenderWindow &window,player gamer,std::vector<invader*> allienLoco, std::vector<bullet*> gekBullets, std::vector<bullet*> gekPlayerBullets, std::vector<barrier*> gekBarriers, bool isPause){
    
    
    window.clear();
    
    //this->initAll();
    this->initPlayer(gamer);
    
    //cout << this->animation;
    this->initInvaders(window,allienLoco);
    this->initBullets(window,gekBullets);
    this->initBullets(window,gekPlayerBullets);
    this->initBarriers(window,gekBarriers);
    this->updateLives(window,gamer);
    this->Animate();
    if(gamer.getLives() == 0) 
        this->gameOver(window,gamer);
    else{
        if(!isPause)
            playing(window,gamer);
        else 
            isPaused(window,gamer);
    }
    
    
    window.display();  

    this->delay();
    //playerSprite.move(sf::Vector2f(5.f, 5.7f)); // offset relative to the current position*/
    }   
    
    void ScreenGen::delay(){
            sf::sleep(delayTime);
    }

#endif
