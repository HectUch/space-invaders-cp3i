#ifndef SCREENGEN_H
#include "ScreenGen.h"
#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#define SCREENGEN_H

using namespace std;

ScreenGen::ScreenGen(sf::RenderWindow &window){    
               
}

void ScreenGen::initPlayer(player elPapito){
   
    this->gamer = elPapito;
     this->playerSprite.setPosition(gamer.getX(),gamer.getY());
   
}

void ScreenGen::initAll(){
    this->LoadTexture();
    delayTime = sf::milliseconds(1000);
    this->initSprites(playerSprite,'C');
    this->initSprites(lifeSprite,'C');
    this->LoadText();    
}

void ScreenGen::initSprites(sf::Sprite &sprite,char type){   
   sprite.setTexture(texture);   
   sprite.setTextureRect(this->catchTextureByType(type,1));
   sprite.setScale(sf::Vector2f(0.3f, 0.3f)); // absolute scale factor
}

sf::IntRect ScreenGen::catchTextureByType(char type,int animation){
    if(type == 'U')
        return sf::IntRect(0, 0, 160, 100);//UFO
    else if((type == 'C') && animation == 1)
        return sf::IntRect(160, 0, 120, 100); //Crab 1
     else if((type == 'C') && animation == 2)
        return sf::IntRect(280, 0, 120, 100);//Crab 2
    else
        return sf::IntRect(0, 0, 160, 100);//UFO
}

void ScreenGen::updateLives(sf::RenderWindow &window,player game){
    if(game.getLives() == 0)return;
    
    else{
        int lifes=game.getLives();
        float point=0;
        for(int i = 0; i < lifes;i++){
                point =60.0+30*i;
                lifeSprite.setPosition(point,560.f);
                window.draw(lifeSprite);
        }
    }
    
}

void ScreenGen::LoadTexture(){ 
     if (texture.loadFromFile("images/allInvaders.png"))
    {
    // error...
    }    
}

void ScreenGen::LoadText(){
 
    if(!font.loadFromFile("fonts/space_invaders.ttf")){
        //Error...
    }
    scoreText.setFont(font);
    scoreText.setString("Score : 0");
    scoreText.setCharacterSize(15);
    scoreText.setFillColor(sf::Color::White);    
    
    shipsText.setFont(font);
    shipsText.setString("Ships : ");
    shipsText.setCharacterSize(15);
    shipsText.setFillColor(sf::Color::White);
    shipsText.setPosition(0.f,570.f);  
    
}

void ScreenGen::gameOver(sf::RenderWindow &window){
    
    gameOvert.setFont(font);
    gameOvert.setString("GAME OVER");
   gameOvert.setCharacterSize(35);
    gameOvert.setFillColor(sf::Color::White);
    gameOvert.setPosition(300.f,250.f);
    
    window.clear();
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
    
    window.display();
    
}

void ScreenGen::Animate(){
    
    
}

void ScreenGen::playing(sf::RenderWindow &window){
      
        window.clear();
        window.draw(playerSprite);
        updateLives(window,gamer);         
        window.draw(scoreText);
        window.draw(shipsText);
        window.display();
        gamer.wasHit();
}

sf::Texture ScreenGen::getTexture(){
    return this->texture;
}

void ScreenGen::drawGame(sf::RenderWindow &window,int score,int lives){
       
    this->initAll();    
    int numberImage = 1;   
    
     
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        scoreTextstring = "Score : " + to_string(score);
        scoreText.setString(scoreTextstring);
        
        if (numberImage == 1){
                                
                playerSprite.setTextureRect(this->catchTextureByType('C',numberImage));//Crab1
                playerSprite.setColor(sf::Color(0,255, 0)); // Rood./ 
                numberImage = 2;
        }
        else
        {
            numberImage = 1;
            playerSprite.setTextureRect(this->catchTextureByType('C',numberImage));//Crab2
            playerSprite.setColor(sf::Color(255,0, 255)); // Rood./
        }
        
        score = 100 + score;
        if(gamer.getLives() == 0) 
            this->gameOver(window);
        
        else{
                playing(window);
        }

        sf::sleep(delayTime);
        playerSprite.move(sf::Vector2f(5.f, 5.7f)); // offset relative to the current position*/
        
    }  

    
}

#endif
