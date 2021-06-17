#ifndef PLAYER_H
#include "element.h"
#define PLAYER_H

class player : public element
{
public:
        player();
        int getScore(void);
private:
        int bullets;
};

#endif
