#ifndef MAIN_CPP
#include "ScreenGen.h"
#include "player.h"
#include "invader.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#define MAIN_CPP

using namespace std;

int main()
{
    player gamer;
    cout << gamer.getLives();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");
    
    ScreenGen myGame(window);
    myGame.initPlayer(gamer);
     myGame.drawGame(window,0,0);
    
    return 0;
}

#endif
