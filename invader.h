#ifndef INVADER_H
#include "element.h"
#define INVADER_H

class invader :  public element
{
public:
        invader();
        invader(float x,float y,char type);
        char getType(void);
        void setType(char);
private:
        int bullets;

};


#endif
