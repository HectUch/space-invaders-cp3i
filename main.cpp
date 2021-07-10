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

int GE_DG;
int DG_GE;
bool GE;
bool DG;
bool run_game_flag;
bool draw_game_flag;

std::vector<invader*> earthDestroyers;//11*5 Invaders
std::vector<bullet*> player_bullets;
std::vector<bullet*> bullets;
std::vector<barrier*> barriers;
player game_player;
invader ufo;
bool pause_state;
bool timer;
bool timing;

system_clock::time_point start;
system_clock::time_point stop;




sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");  //For now , this have to be generate a 800x600, there is no automated way to re-scale screen
ScreenGen myGame(window);
gameEngine gameMechanics;

void* draw_the_game(void *){
    //cout << "26" << "\n";
    //myGame.drawGameWithEngine(window,gameMechanics);
    //myGame.drawGame(window,gameMechanics.getPlayer(),gameMechanics.getInvaders(),gameMechanics.getBullets(), gameMechanics.getPlayerBullets(), gameMechanics.getBarriers(),gameMechanics.paused(), gameMechanics.getTimer());
    //start = high_resolution_clock::now();
    myGame.drawGame(window,game_player,earthDestroyers,bullets, player_bullets, barriers, ufo, pause_state, timer);
    //stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds> (stop - start);
    //cout << duration.count() << endl;
    draw_game_flag = true;
    
    //cout << "27" << "\n";
    
    return NULL;
    
}

//void* run_the_game(void *){
    
    ////gameMechanics.runGame(input);
    //cout << "6" << "\n";
    //gameMechanics.runGame();
    //cout << "7" << "\n";
    //run_game_flag = true;
    //cout << "8" << "\n";
    
    //return NULL;
    
//}



int main()
{   
    cout << "Generating Screen\n";
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");  //For now , this have to be generate a 800x600, there is no automated way to re-scale screen  
    //ScreenGen myGame(window);
    cout << "Loading Game...\n";
    //gameEngine gameMechanics;
        
    myGame.splashScreen(window);//Create a initial screen before the game    
    //A menu to make the game more presentable, it
    
    //Threads creation
    pthread_t run_game;
    pthread_t draw_game;
    
    GE_DG = 0;
    DG_GE = 2;
    
    GE = true;
    DG = true;
    
    run_game_flag = false;
    draw_game_flag = false;
    
    timing = true;
    
    while (window.isOpen())
    {     
        
        //if(gameMechanics.exitGame()){
            //window.close();
            //return 0;        
        //}    
    
        sf::Event event;    
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //if(run_game_flag){
                //cout << "9" << "\n";
                //pthread_join(run_game, NULL);
                //cout << "10" << "\n";
                //PlayerBullets = gameMechanics.getPlayerBullets();
                //cout << "11" << "\n";
                //run_game_flag = false;
                //cout << "12" << "\n";
                //GE = true;
                //cout << "13" << "\n";
                //GE_DG++;
        //}
        
        if(draw_game_flag){
                //cout << "28" << "\n";
                pthread_join(draw_game, NULL);
                //cout << "29" << "\n";
                draw_game_flag = false;
                //cout << "30" << "\n";
                DG = true;
                //cout << "31" << "\n";
                DG_GE++;
                //cout << "32" << "\n";
                stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds> (stop - start);
                cout << duration.count() << endl;
        }
        
        if((GE_DG > 0) && DG){
            start = high_resolution_clock::now();
            //start = high_resolution_clock::now();
            //cout << "21" << "\n";
            --GE_DG;
            //cout << "22" << "\n";
            DG = false;
            //cout << "23" << "\n";
            draw_game_flag = false;
            //cout << "24" << "\n";
            pthread_create(&draw_game, NULL, draw_the_game, NULL);
            //cout << "25" << "\n";    
        }
        
        if((DG_GE > 0) && GE){
            //cout << "1" << "\n";
            --DG_GE;
            //cout << "2" << "\n";
            GE = false;
            //cout << "3" << "\n";
            run_game_flag = false;
            //cout << "4" << "\n";
            //pthread_create(&run_game, NULL, run_the_game, NULL);
            //start = high_resolution_clock::now();
            gameMechanics.runGame();
            //stop = high_resolution_clock::now();
            //auto duration = duration_cast<microseconds> (stop - start);
            //cout << duration.count() << endl;
            game_player = gameMechanics.getPlayer();
            earthDestroyers = gameMechanics.getInvaders();
            bullets = gameMechanics.getBullets();
            player_bullets = gameMechanics.getPlayerBullets();
            barriers = gameMechanics.getBarriers();
            ufo = gameMechanics.getUFO();
            pause_state = gameMechanics.paused();
            timer = gameMechanics.getTimer();
            GE = true;
            GE_DG++;
            //start = high_resolution_clock::now();
            //stop = high_resolution_clock::now();
            //auto duration = duration_cast<microseconds> (stop - start);
            //cout << duration.count() << endl;
            //cout << "5" << "\n";
        }
        
        
        
        //myGame.drawGameWithEngine(window,gameMechanics); 
    
        //auto start = high_resolution_clock::now();
        
        //auto stop = high_resolution_clock::now();
        //auto duration = duration_cast<microseconds> (stop - start);
        //cout << duration.count() << endl;

        //sf::sleep(sf::milliseconds(100));
  
        }
        
        return 0;
}
#endif
