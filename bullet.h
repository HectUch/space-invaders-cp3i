#ifndef BULLET_H

#define BULLET_H

class bullet{
public:    
        bullet(float, float);
        float getX(void );
        float getY(void ); 
        void setPosition(float);
        void shootByInvader();
        int getDirection();        
private:
        float x,y;
        int direction;
};

#endif
