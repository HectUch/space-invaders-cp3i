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
#include <string>
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
        
    myGame.splashScreen(window);//Create a initial screen before the game    
    //A menu to make the game more presentable, it
    
    //Threads creation
    pthread_t run_game;
    pthread_t draw_game;
    
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
        myGame.drawGameWithEngine(window,gameMechanics); 
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds> (stop - start);
        cout << duration.count() << endl;

    //sf::sleep(sf::milliseconds(100));
  
        }
        
        return 0;
}
#endif
