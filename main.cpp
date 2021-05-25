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
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        if (event.type == sf::Event::Closed)
                window.close();
        }
    
    
        myGame.initPlayer(gamer);
        myGame.drawGame(window,gamer,invaders,ufo,barriers); //idea on how pass the player
    
    }
    return 0;
}

#endif
