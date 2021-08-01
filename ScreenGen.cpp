#ifndef SCREENGEN_H
#include "ScreenGen.h"
#include "element.h"
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include "gameEngine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <chrono>
#define SCREENGEN_H

using namespace std;

using namespace std::chrono;

ScreenGen::ScreenGen(sf::RenderWindow &window){    
        animation = 1;
        this->LoadText();   
        //this->initAll();
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

void  ScreenGen::initUFO(sf::RenderWindow &window, invader UFO){
    
        this->initSprites(invadersSprite,UFO.getType());   
        this->invadersSprite.setPosition(UFO.getX(),UFO.getY());
        if(animation == 1){
            invadersSprite.setColor(sf::Color(255,255, 255));
        }
        else{
            invadersSprite.setColor(sf::Color(255,0, 0));
        }
        window.draw(invadersSprite);
        
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
      for(int i = 0; i < 10; i++){
           
            textBoxAux.setFont(font);
            textBoxAux.setString("The C++ Jongens  Presents : ");
            textBoxAux.setCharacterSize(35);
            textBoxAux.setFillColor(sf::Color(color,color,color));
            textBoxAux.setPosition(100.f,250.f);            
            
            window.draw(textBoxAux);
            color = color - 25*i;          

        window.display();  
        this->delay();
        
       
      }
      this->initAll();      
  }
  
void ScreenGen::MainMenu(sf::RenderWindow &window,int option){
            
            float optie = option + 0.0f;

            window.clear();
            textBoxAux.setFont(font);
            textBoxAux.setString("Enschede Invaders ");
            textBoxAux.setCharacterSize(35);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(190.f,180.f);             
            window.draw(textBoxAux);
            
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
            
            textBoxAux.setFont(font);
            textBoxAux.setString("Start Game ");
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(300.f,270.f);             
            window.draw(textBoxAux);      
            
            textBoxAux.setFont(font);
            textBoxAux.setString("High-Score ");
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(300.f,310.f);             
            window.draw(textBoxAux);
            
            textBoxAux.setFont(font);
            textBoxAux.setString("About the Game");
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(265.f,350.f);             
            window.draw(textBoxAux);
           
            textBoxAux.setFont(font);
            textBoxAux.setString("Exit ");
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(360.f,390.f);             
            window.draw(textBoxAux);
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
    if (!htexture.loadFromFile("images/hector.jpg"))
    {
        // error...
            cout << "Could not load texture/n";
    }
    if (!atexture.loadFromFile("images/alain.jpg"))
    {
        // error...
            cout << "Could not load texture/n";
    }
    if (!rtexture.loadFromFile("images/remm1.png"))
    {
        // error...
            cout << "Could not load texture/n";
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

void ScreenGen::yourScore(sf::RenderWindow &window,string first, int score){        
        
            
            textBoxAux.setFont(font);
            textBoxAux.setString("Type your Score ( Use Up or Down) : " );
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(100.f,180.f);             
            window.draw(textBoxAux);
            
            textBoxAux.setFont(font);
            textBoxAux.setString(first  + " : " + to_string(score));
            textBoxAux.setCharacterSize(20);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(200.f,220.f);             
            window.draw(textBoxAux);   
            
}

void ScreenGen::levelUp(sf::RenderWindow &window,int level){
        
        
            window.clear();
            textBoxAux.setFont(font);
            textBoxAux.setString("LEVEL " + to_string(level)  );
            textBoxAux.setCharacterSize(35);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(300.f,180.f);             
            window.draw(textBoxAux);
            
 
                this->initSprites(invadersSprite,'A');   
                this->invadersSprite.setPosition(300.f,270.f);
                window.draw(invadersSprite);
       

                this->initSprites(invadersSprite,'B');   
                this->invadersSprite.setPosition(300.f,310.f);
                window.draw(invadersSprite);
               
 
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(300.f,350.f);
                window.draw(invadersSprite);


                this->initSprites(invadersSprite,'U');   
                this->invadersSprite.setPosition(300.f,390.f);
                window.draw(invadersSprite);
      
            
            textBoxAux.setFont(font);
           textBoxAux.setString(" = < " + to_string(level*100) + " >" );
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(360.f,270.f);             
            window.draw(textBoxAux);      
            
            textBoxAux.setFont(font);
            textBoxAux.setString(" = < " + to_string(level*200) + " >" );
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(360.f,310.f);             
            window.draw(textBoxAux);
            
            textBoxAux.setFont(font);
            textBoxAux.setString(" = < " + to_string(level*300) + " >" );
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(360.f,350.f);             
            window.draw(textBoxAux);
           
            textBoxAux.setFont(font);
            textBoxAux.setString(" = < ? >" );
            textBoxAux.setCharacterSize(25);
            textBoxAux.setFillColor(sf::Color::White);
            textBoxAux.setPosition(360.f,390.f);             
            window.draw(textBoxAux);
            window.display();  
            this->Animate();       
        
        
}

void ScreenGen::highScore(sf::RenderWindow &window,string first,string second, string third){
    
        window.clear();  
                
        textBoxAux.setFont(font);
        textBoxAux.setString("HIGH SCORES");
        textBoxAux.setCharacterSize(35);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(300.f,250.f);    
    
        window.draw(textBoxAux);
            
        textBoxAux.setFont(font);
        textBoxAux.setString(first);
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(335.f,300.f);
        window.draw(textBoxAux);
             
        textBoxAux.setFont(font);
        textBoxAux.setString(second);
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(335.f,330.f);
    
        window.draw(textBoxAux);      
    
        textBoxAux.setFont(font);
        textBoxAux.setString(third);
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(335.f,360.f);
    
        window.draw(textBoxAux);
        
        textBoxAux.setFont(font);
        textBoxAux.setString("PRESS ENTER TO GO BACK");
        textBoxAux.setCharacterSize(10);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(330.f,420.f);
    
        window.draw(textBoxAux);  
        window.display();    
}

void ScreenGen::gameOver(sf::RenderWindow &window,int option){
    
        window.clear();  
    
        if(option%2 == 0){
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(290.f,300.f);
                window.draw(invadersSprite);
                this->invadersSprite.setPosition(470.f,300.f);
                window.draw(invadersSprite);            
        }
        else if(option%2 == 1){
                this->initSprites(invadersSprite,'C');   
                this->invadersSprite.setPosition(290.f,330.f);
                window.draw(invadersSprite);
                this->invadersSprite.setPosition(475.f,330.f);
                window.draw(invadersSprite);
        }
            
        textBoxAux.setFont(font);
        textBoxAux.setString("GAME OVER");
        textBoxAux.setCharacterSize(35);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(300.f,250.f);    
    
        window.draw(scoreText);
        window.draw(textBoxAux);
            
        textBoxAux.setFont(font);
        textBoxAux.setString("RESTART");
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(335.f,300.f);
        window.draw(textBoxAux);
             
        textBoxAux.setFont(font);
        textBoxAux.setString("QUIT GAME");
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(325.f,330.f);
    
        window.draw(textBoxAux);  
        window.display();    
}

void ScreenGen::aboutTheGame(sf::RenderWindow &window){
    
        window.clear();          
        //This is us 
        
        sf::Sprite theBoys;
        theBoys.setTexture(htexture);
        theBoys.setScale(sf::Vector2f(0.03f, 0.03f));
        theBoys.setPosition(550.f,150.f);
        window.draw(theBoys);
        
        
        theBoys.setTexture(rtexture);
        theBoys.setScale(sf::Vector2f(0.03f, 0.03f));
        theBoys.setPosition(550.f,450.f);
        window.draw(theBoys);
        
        textBoxAux.setFont(font);
        textBoxAux.setString("Heitor Uchoa");
        textBoxAux.setCharacterSize(15);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(550.f,250.f);
        window.draw(textBoxAux);
        
        
        textBoxAux.setFont(font);
        textBoxAux.setString("Remmelt Fopma");
        textBoxAux.setCharacterSize(15);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(545.f,550.f);
        window.draw(textBoxAux);
        
        textBoxAux.setString("ABOUT THE GAME");
        textBoxAux.setCharacterSize(35);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(220.f,10.f);   
        window.draw(textBoxAux);        
        
        textBoxAux.setFont(font);
        textBoxAux.setString("TEAM");
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(535.f,100.f);
        window.draw(textBoxAux);
        float x = 40.f;   
        textBoxAux.setFont(font);
        textBoxAux.setString("CONTROLS");
        textBoxAux.setCharacterSize(25);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(15.f,95.f);
        window.draw(textBoxAux);
             
        textBoxAux.setFont(font);
        textBoxAux.setString("LEFT ARROW : MOVE PLAYER LEFT");
        textBoxAux.setCharacterSize(20);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(15.f,130.f+x);    
        window.draw(textBoxAux); 
        
        textBoxAux.setFont(font);
        textBoxAux.setString("RIGHT ARROW : MOVE PLAYER RIGHT");
        textBoxAux.setCharacterSize(20);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(15.f,165.f+x);    
        window.draw(textBoxAux);  
        
        textBoxAux.setFont(font);
        textBoxAux.setString("SPACE BAR : SHOOT BULLETS");
        textBoxAux.setCharacterSize(20);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(15.f,200.f+x);    
        window.draw(textBoxAux);  
        
        textBoxAux.setFont(font);
        textBoxAux.setString("P : PAUSE GAME");
        textBoxAux.setCharacterSize(20);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(15.f,235.f+x);    
        window.draw(textBoxAux);  
        
        textBoxAux.setFont(font);
        textBoxAux.setString("ESCAPE : EXIT GAME");
        textBoxAux.setCharacterSize(20);
        textBoxAux.setFillColor(sf::Color::White);
        textBoxAux.setPosition(15.f,270.f+x);    
        window.draw(textBoxAux);
        
        window.display();    
        
}

void ScreenGen::Animate(){    
    if(this->animation == 1){
        this->animation = 2;
    }
    else{
        this->animation =1;
    }    
}

void ScreenGen::playing(sf::RenderWindow &window,player gamer){              
        window.draw(playerSprite);
        updateLives(window,gamer);         
        window.draw(scoreText);
        window.draw(shipsText);               
}

sf::Texture ScreenGen::getTexture(){
    return this->texture;
}

void ScreenGen::initBullets(sf::RenderWindow &window, std::vector<bullet*> bulletss1){    
        for(int n = 0; n < bulletss1.size(); n++){
               sf::Sprite bulletsSprite;
               this->initSprites(bulletsSprite,'Q');
               bulletsSprite.setPosition(bulletss1[n]->getX(),bulletss1[n]->getY());
               bulletsSprite.setColor(sf::Color(255,0, 255)); // Rood./
               window.draw(bulletsSprite);
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
    textBoxAux.setFont(font);
    textBoxAux.setString("PAUSED");
    textBoxAux.setCharacterSize(35);
    textBoxAux.setFillColor(sf::Color::White);
    textBoxAux.setPosition(300.f,250.f);
    window.draw(scoreText);
    window.draw(textBoxAux);
    window.draw(playerSprite);
    updateLives(window,gamer);   
}

void ScreenGen::drawGameWithEngine(sf::RenderWindow &window,gameEngine &gameState){
    
    if(gameState.getScreen() == 0){
       this->MainMenu(window,gameState.getOption());
        return;
    }
    
    else if(gameState.getScreen() == 1){
    
        window.clear();
        
        this->initPlayer(gameState.getPlayer());   
        if (gameState.getTimer()){
            this->Animate();   
        }    
        this->initInvaders(window,gameState.getInvaders());
        this->initBullets(window,gameState.getBullets());
        this->initBullets(window,gameState.getPlayerBullets());
        this->initBarriers(window,gameState.getBarriers());
        this->updateLives(window,gameState.getPlayer());
        this->initUFO(window, gameState.getUFO());

        if(!(gameState.paused()))
            playing(window,gameState.getPlayer());
        else if(!(gameState.getPlayer().isAlive()))
            yourScore(window,gameState.getCharPos(), gameState.getPlayer().getScore());
        else
            isPaused(window,gameState.getPlayer());    
        
        window.display();
    }
    else if(gameState.getScreen() == 6){
        this->levelUp(window,gameState.getLevel());   
        
    }
    else if(gameState.getScreen() == 2){
              this->highScore(window,gameState.getPosScore(1),gameState.getPosScore(2),gameState.getPosScore(3)); 
     }
    else if(gameState.getScreen() == 3){
              this->aboutTheGame(window); 
     }    
    else if(gameState.getScreen() == 5){
        this->gameOver(window,gameState.getOption());        
    }

    
}

void ScreenGen::drawGame(sf::RenderWindow &window,player gamer,std::vector<invader*> allienLoco, std::vector<bullet*> gekBullets, std::vector<bullet*> gekPlayerBullets, std::vector<barrier*> gekBarriers, bool isPause, bool Timer){
    
    window.clear();
    
    this->initPlayer(gamer);
    
    if (Timer){
        this->Animate();   
    }
    
    this->initInvaders(window,allienLoco);
    this->initBullets(window,gekBullets);
    this->initBullets(window,gekPlayerBullets);
    this->initBarriers(window,gekBarriers);
    this->updateLives(window,gamer);

     if(!isPause)
        playing(window,gamer);
    else 
        isPaused(window,gamer);    
    
    window.display();   

}   
    
void ScreenGen::delay(){
    sf::sleep(delayTime);
}

#endif
