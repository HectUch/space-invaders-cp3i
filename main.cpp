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
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#define MAIN_CPP

using namespace std;

using namespace std::chrono;

int main()
{   
    
    cout << "Generating Screen\n";
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");  //For now , this have to be generate a 800x600, there is no automated way to re-scale screen  
    ScreenGen myGame(window);
    cout << "Loading Game...\n";
    gameEngine gameMechanics;
    //cout << gameEngine->getInvaders().size();
        
    myGame.splashScreen(window);//Create a initial screen before the game, later in the project
    
    while(gameMechanics.getScreen() == 0){
        myGame.MainMenu(window,gameMechanics.getOption());
    }
    

    while (window.isOpen())
    {
     
    if(gameMechanics.exitGame()){
        window.close();
        return 0;        
    }
    
    sf::Event event;    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    gameMechanics.runGame();
    
    auto start = high_resolution_clock::now();
    myGame.drawGame(window,gameMechanics.getPlayer(),gameMechanics.getInvaders(),gameMechanics.getBullets(), gameMechanics.getPlayerBullets(), gameMechanics.getBarriers(),gameMechanics.paused(), gameMechanics.getTimer());//This will be responsible for the entire inteligence/operation of the game, collision detection, control of invaders, shoots and so on
    //is it possible to do the comunication in between both as a FIFO buffer?
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds> (stop - start);
    cout << duration.count() << endl;
    //Is the UFO one more invaders generated dynamically like bullets? Decision we should take as a group.
    //myGame.drawGame(window,gameMechanics.getPlayer(),gameMechanics.getInvaders(),gameMechanics.getBullets(), gameMechanics.getPlayerBullets(), gameMechanics.getBarriers(),gameMechanics.paused());//This class does not have any inteligence, it only reads outputs from the game Engine class and prints in the screen
    //myGame.updatePlayer(wind ow, gameMechanics.getPlayer(), gameMechanics.paused());
    
    //sf::sleep(sf::milliseconds(100));
    //This class does not have any inteligence, it only reads outputs from the game Engine class and prints in the screen    
}
    
    return 0;
}

#endif
