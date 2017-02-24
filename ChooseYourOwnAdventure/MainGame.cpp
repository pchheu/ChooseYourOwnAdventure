//
//  MainGame.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "MainGame.hpp"
#include "Map.hpp"
#include "Sprite.hpp"

//Helper function incase the window was unable to be created
void fatalError(std::string errorString){
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit..." << std::endl;
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

MainGame::MainGame(){
    window = nullptr;
    screenWidth = 1024;
    screenHeight = 700;
    
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
    
    if(window == nullptr){
        fatalError("SDL Window could not be created.");
    }
    
    //Initializes the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
}

void MainGame::gameLoop(){
    /*Test stuff
    SDL_Texture* map = nullptr;
    map = IMG_LoadTexture(renderer, "Images/map.bmp");
    if(map == NULL){
        std::cout << "Image could not be loaded" << std::endl;
    }
    
    SDL_Rect map_rect;
    map_rect.x = 0;
    map_rect.y = 0;
    map_rect.w = 1200;
    map_rect.h = 750;
    
     */
    
    Map a = *new Map("Images/map.bmp");
    
    while(currentState != GameState::EXIT){
        processInput();
        
        SDL_RenderClear(renderer);
        
        a.renderMap();
        
        SDL_RenderPresent(renderer);
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
