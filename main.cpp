#ifndef MAIN_CPP
#include "ScreenGen.h"
#include "player.h"
#include "invader.h"
#include "bullet.h"
#include "barrier.h"
#include "gameEngine.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#define MAIN_CPP

using namespace std;

int main()
{   
    
    cout << "Generating Screen\n";
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");  //For now , this have to be generate a 800x600, there is no automated way to re-scale screen  
    ScreenGen myGame(window);
    cout << "Loading Game...\n";
    gameEngine gameMechanics;
    //cout << gameEngine->getInvaders().size();
        
    //myGame.splashScreen(window);//Create a initial screen before the game, later in the project
    
    while (window.isOpen())
    {    
        
    
    sf::Event event;
    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    
    gameMechanics.runGame();//This will be responsible for the entire inteligence/operation of the game, collision detection, control of invaders, shoots and so on
    //is it possible to do the comunication in between both as a FIFO buffer?
    
    //Is the UFO one more invaders generated dynamically like bullets? Decision we should take as a group.
    myGame.drawGame(window,gameMechanics.getPlayer(),gameMechanics.getInvaders(),gameMechanics.getBullets(), gameMechanics.getPlayerBullets(), gameMechanics.getBarriers(),gameMechanics.paused());//This class does not have any inteligence, it only reads outputs from the game Engine class and prints in the screen
    if(gameMechanics.exitGame()){
        window.close();
        return 0;
        
    }
    
}
    
    return 0;
}

#endif
