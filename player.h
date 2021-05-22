#ifndef PLAYER_H

#define PLAYER_H


class player{
public:    
        player();
        int getLives(void );
        void wasHit(void );
        int getScore(void);
        float getX(void );
        float getY(void );
 
private:
        int score;
        float x,y;
        int lives;
        int bullets;   
};

#endif
