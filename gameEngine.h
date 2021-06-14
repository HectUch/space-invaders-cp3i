#ifndef GAMEENGINE_H
#include <SFML/Audio.hpp>
#include "ScreenGen.h"
#include "player.h"
#include "bullet.h"
#include "barrier.h"
#include "invader.h"
#include <vector>
#define GAMEENGINE_H

class gameEngine{
public:
        gameEngine();
        void runGame();
        void restartGame();
        void pause();
        player getPlayer();
        std::vector<invader*> getInvaders();
        std::vector<bullet*> getBullets();
        std::vector<barrier*> getBarriers();
         int initSound( );        
private:
        void collision();
        void invadersShoot();
        int timesOneSide;
        int lastShoot;
        int level;
        int randomShootingTime;
        int invadersDirection;
        int gameSpeed;
        void readInput();
        void moveBullets();
        bool isBulletInTheArea(bullet,invader);
        void invadersCometoEarth(void);
        void shootSound( );     
        player *gamer;
        std::vector<invader*> earthDestroyers;//11*5 Invaders
        std::vector<bullet*> bullets;
        std::vector<barrier*> barriers;
        invader ufo; 
        
        //Sound Effects
        sf::Sound *sound;
        sf::SoundBuffer *buffer;
};

#endif
