#ifndef INVADER_H

#define INVADER_H


class invader{
public:    
        invader();
        float getX(void );
        float getY(void );
        int getScore(void);
  
private:
        int score;
        float x,y;
        int lives;
        int bullets;
   
};

#endif
