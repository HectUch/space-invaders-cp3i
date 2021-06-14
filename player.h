#ifndef PLAYER_H

#define PLAYER_H


class player{
public:    
        player();
        void setPosition(float);
        int getLives(void );
        void wasHit(void );
        int getScore(void);
        void setScore(int Score);
        float getX(void );
        float getY(void );
 
private:
        int score;
        float x,y;
        int lives;
        int bullets;   
};

#endif
