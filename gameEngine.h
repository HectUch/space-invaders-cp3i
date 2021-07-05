#ifndef GAMEENGINE_H
#include <SFML/Audio.hpp>
#include "player.h"
#include "bullet.h"
#include "element.h"
#include "barrier.h"
#include "invader.h"
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#define GAMEENGINE_H

class gameEngine{
public:
        gameEngine();
        void runGame();
        void restartGame();
        bool paused();
        player getPlayer();
        std::vector<invader*> getInvaders();
        std::vector<bullet*> getBullets();
        std::vector<bullet*> getPlayerBullets();
        std::vector<barrier*> getBarriers();
        bool getTimer();
        int initSound( );
        bool exitGame();
        int getOption();
        int getScreen();
        void initInvaders();
        void readInput();
         
private:
        void initBarriers(int,int);
        bool isBulletInTheArea(bullet, player);
        bool isBulletInTheArea(bullet, barrier);
        void collision();
        void invadersShoot();
        int timesOneSide;
        int lastShoot;
        int level;
        int randomShootingTime;
        int invadersDirection;
        int gameSpeed;
        int screen;
        int option;
        void moveBullets();
        bool isBulletInTheArea(bullet,invader);
        void invadersCometoEarth();
        void shootSound( );     
        player *gamer;
        std::vector<invader*> earthDestroyers;//11*5 Invaders
        std::vector<invader*> earthDestroyersShooters;//ShootingInvaders
        std::vector<bullet*> player_bullets;
        std::vector<bullet*> bullets;
        std::vector<barrier*> barriers;
        invader ufo; 
        bool pause;
        bool exit;
        //Sound Effects
        sf::Sound *sound;
        sf::SoundBuffer *buffer;
        pthread_t invaders_come_to_earth;
        pthread_t move_bullets;
        clock_t timeDelay_invader;
        clock_t timeDelay_bullet;
        bool timer;
        bool shoot_state;
};

#endif
