//
//  MainGame.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "MainGame.hpp"

MainGame::MainGame(){
    window = nullptr;
    screenWidth = 1024;
    screenHeight = 650;
    
    currentState = GameState::PLAY;
}

MainGame::~MainGame(){
    
}

void MainGame::run(){
    initSystems();
    gameLoop();
}

void MainGame::initSystems(){
    //Initializes SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = SDL_CreateWindow("ChooseYourOwnAdventure",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth,
                              screenHeight,
                              SDL_WINDOW_OPENGL);
}

void MainGame::gameLoop(){
    
    while(currentState != GameState::EXIT){
        processInput();
    }
}

void MainGame::processInput(){
    SDL_Event evnt;
    
    while(SDL_PollEvent(&evnt) == true){
        switch (evnt.type) {
            case SDL_QUIT:
                currentState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
    }
}
