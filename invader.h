#ifndef INVADER_H

#define INVADER_H

class invader 
{
public:
        invader();
        invader(float x,float y,char type);
        void recruitToWar(int score,char type);
        char getType(void);
        void setType(char);
        float getX(void);
        float getY(void);
        int getScore(void);
        void setScore(int Score);
        void setPosition(float,float);
        void getHit();
        bool isAlive();
        void setPosition(float);       
        int getLives(void );
        void wasHit(void );
        
private:
    
        int score;
        float x,y;
        int lives;
        char type;
        int bullets;

};


#endif
