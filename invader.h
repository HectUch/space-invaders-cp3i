#ifndef INVADER_H

#define INVADER_H


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
   
};

#endif
