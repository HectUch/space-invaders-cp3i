#ifndef PLAYER_H

#define PLAYER_H

class player 
{
    
public:
        player();
        int getScore(void);
        char getType(void);
        void setType(char);
        float getX(void);
        float getY(void);
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
