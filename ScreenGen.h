#ifndef SCREENGEN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "player.h"
#include "bullet.h"
#include "invader.h"
#include <vector>
#define SCREENGEN_H

using namespace std;

class ScreenGen{
public:    
    ScreenGen(sf::RenderWindow &);
    void splashScreen();
    void drawGame(sf::RenderWindow &,player,std::vector<invader*>,std::vector<bullet*>); 
    void reset();
    void pauseScreen();
    void readInput();
 
private:
    sf::Texture getTexture();
    void LoadText();
    void initBullets(sf::RenderWindow &,std::vector<bullet*> ); 
    void initSprites(sf::Sprite&,char);
    sf::IntRect catchTextureByType(char,int);    
    void initPlayer(player);
    void initInvaders(sf::RenderWindow &,std::vector<invader*>);    
    void initBullets(std::vector<bullet*>);    
    void gameOver(sf::RenderWindow &window,player);
    void playing(sf::RenderWindow &window,player);
    void updateLives(sf::RenderWindow &window,player);
    void initAll();
    void Animate();
    void LoadTexture();
    string scoreTextstring;     
    sf::Sprite invadersSprite;
    sf::Sprite playerSprite;
    sf::Sprite lifeSprite;
    sf::Sprite sprite;
    sf::Sprite bulletsSprite;
    sf::Sprite ufoSprite;
    sf::Sprite blockSprite;
    sf::Texture texture;
    sf::Texture texturePlayer;
    sf::Text scoreText;
    sf::Text shipsText;
    sf::Text splashScreenText;
    sf::Text gameOvert;
    sf::Font font;
    sf::Time delayTime;
    int animation;
    
};

#endif
