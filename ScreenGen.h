#ifndef SCREENGEN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include "gameEngine.h"
#include <vector>
#define SCREENGEN_H

using namespace std;

class ScreenGen{
    
public:    
    
    ScreenGen(sf::RenderWindow &);
    void splashScreen(sf::RenderWindow &);
    void drawGameWithEngine(sf::RenderWindow &,gameEngine&);
    void drawGame(sf::RenderWindow &,player,std::vector<invader*>,std::vector<bullet*>, std::vector<bullet*>, std::vector<barrier*>,bool isPause, bool); 
    void reset();
    void pauseScreen();
    void MainMenu(sf::RenderWindow &,int);
    void gameOver(sf::RenderWindow &window,int);
    void highScore(sf::RenderWindow &window,string first,string second, string third);
    void AboutTheGame();
    void levelUp(sf::RenderWindow &window,int level);
    void aboutTheGame(sf::RenderWindow &);
    void yourScore(sf::RenderWindow &,string, int);
    
private:
    
    sf::Texture getTexture();
    void LoadText();
    void delay();
    void initBullets(sf::RenderWindow &,std::vector<bullet*> ); 
    void initBarriers(sf::RenderWindow &,std::vector<barrier*> ); 
    void initSprites(sf::Sprite&,char);
    sf::IntRect catchTextureByType(char,int);    
    void initPlayer(player);
    void initInvaders(sf::RenderWindow &,std::vector<invader*>);    
    void initBullets(std::vector<bullet*>);    
    void playing(sf::RenderWindow &window,player);
    void updateLives(sf::RenderWindow &window,player);
    void initAll();
    void Animate();
    void LoadTexture();
    void isPaused(sf::RenderWindow &window,player gamer);
    void  initUFO(sf::RenderWindow &, invader);
    
     sf::Texture textureExplosion;
    string scoreTextstring;     
    sf::Sprite invadersSprite;
    sf::Sprite playerSprite;
    sf::Sprite lifeSprite;
    sf::Sprite sprite;
    sf::Sprite bulletsSprite;
    sf::Sprite ufoSprite;
    sf::Sprite blockSprite;
    sf::Texture texture;
    sf::Texture htexture,atexture,rtexture;
    sf::Texture textureAll;
    sf::Texture texturePlayer;
    sf::Texture textureProjectile;
    sf::Text scoreText;
    sf::Text shipsText; 
    sf::Text splashScreenText;
    sf::Text textBoxAux;
    sf::Font font;
    sf::Time delayTime;
    int menu;
    int animation;
    
};

#endif
