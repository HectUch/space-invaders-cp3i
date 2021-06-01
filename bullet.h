#ifndef BULLET_H

#define BULLET_H

class bullet{
public:    
        bullet(float, float);
        float getX(void );
        float getY(void ); 
        void setPosition(float);
private:
        float x,y;   
};

#endif
