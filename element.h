#ifndef ELEMENT_H

#define ELEMENT_H

class element{
public:    
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
        int score;
        float x,y;
        int lives;
        char type;
};

#endif
