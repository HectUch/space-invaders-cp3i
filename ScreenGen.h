#ifndef SCREENGEN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "player.h"
#define SCREENGEN_H

using namespace std;

class ScreenGen{
public:    
    ScreenGen(sf::RenderWindow &);
    void drawGame(sf::RenderWindow &,int,int );
    void initSprites(sf::Sprite&,char);
    sf::Texture getTexture();
    void LoadText();
    void initPlayer(player);
    void initInvaders();
    sf::IntRect catchTextureByType(char,int);

    
    
 
private:
    void gameOver(sf::RenderWindow &window);
    void playing(sf::RenderWindow &window);
    void updateLives(sf::RenderWindow &window,player game);
    void initAll();
    void Animate();
    void LoadTexture();
    player gamer;
    string scoreTextstring;     
    sf::RenderWindow *gameScreen;//(sf::VideoMode(800, 600), "Space Invaders");
    sf::Sprite invadersSprite;
    sf::Sprite playerSprite;
    sf::Sprite lifeSprite;
    sf::Sprite sprite;
    sf::Sprite bulletsSprite;
    sf::Sprite ufoSprite;
    sf::Sprite blockSprite;
    sf::Texture texture;
    sf::Text scoreText;
    sf::Text shipsText;
    sf::Text splashScreen;
    sf::Text gameOvert;
    sf::Font font;
    sf::Time delayTime;    
    
};

#endif
