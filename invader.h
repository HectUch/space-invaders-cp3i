#ifndef INVADER_H
#include "element.h"
#define INVADER_H

class invader :  public element
{
public:    
        invader();
        invader(float x,float y,char type);
        char getType(void);
private:
        int bullets;
   
};

/*

class invader{
public:    
        invader();
        invader(float x,float y,char type);
        float getX(void);
        float getY(void);
        int getScore(void);
        char getType(void);
        void setPosition(float,float);
        void getHit();
        bool isAlive();
private:
        int score;
        char type;
        float x,y;
        int lives;
        int bullets;
   
};*/

#endif
