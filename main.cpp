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

typedef void * (*THREADFUNCPTR)(void *);

gameEngine gameMechanics; //intialize game engine

sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders"); //initialize window

ScreenGen myGame(window); //create window

bool input[8]; //LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, SPACE = 4, ENTER = 5, P = 6, ESC = 7 

void* draw_the_game(void *){ //function which the threading can use to execute the drawing of the game
        
    myGame.drawGameWithEngine(window,gameMechanics);
    
    return NULL;
    
}

void* readInput(void *){ //function which reads the input and updates the input array accordingly
    
for(int i = 0; i < 8; i++){
    
    input[i] = false;
    
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
             input[7] = true;
}    

if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ){//&& this->gamer->getLives() > 0 ){
             input[6] = true;
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
             input[0] = true;
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
             input[1] = true;
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
             input[4] = true;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
             input[2] = true;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
             input[3] = true;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
             input[5] = true;
}

return NULL;

}

int main()
{   

    cout << "Generating Screen\n";

    cout << "Loading Game...\n";

    myGame.splashScreen(window);//Create a initial screen before the game    
    
    //Threads creation
    pthread_t draw_game;
    
    bool B_1 = false;//boolean to represent the token from Game Engine to Input and Draw Game
    bool B_2 = true;//boolean to represent the token from Input to Game Engine
    bool B_3 = true;//boolean to represent the tokenDraw Game to Game Engine
  
    while (window.isOpen())
    {     
        
        if(gameMechanics.exitGame()){ //when the game is exited, close the window
            window.close();
            return 0;        
        }    
    
        sf::Event event;    
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //when the windwo is closed, close the window
                window.close();
        }
        
        if(B_2 && B_3){ //when input and draw game are finished, perform run game

            B_2 = false;
            B_3 = false;
            
            gameMechanics.runGame(input);
        
            B_1 = true;
            
        }
        
        if(B_1){ //when run game is finished, perform read input and draw game
            
            B_1 = false;
            
            pthread_create(&draw_game, NULL, draw_the_game, NULL); //execute draw game in thread
            
            readInput(NULL); //execute read input in main thread
            
            pthread_join(draw_game, NULL);
        
            B_2 = true;
            B_3 = true;
            
            
        }

        }
        
        return 0;
}
#endif
