#ifndef GAMEENGINE_H
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
               
private:
        void collision();
        int timesOneSide;
        int level;
        int invadersDirection;
        int gameSpeed;
        void readInput();
        void moveBullets();
        bool isBulletInTheArea(bullet,invader);
        void invadersCometoEarth(void);
        
        player *gamer;
        std::vector<invader*> earthDestroyers;//11*5 Invaders
        std::vector<bullet*> bullets;
        std::vector<barrier*> barriers;
        invader ufo;        
};

#endif
