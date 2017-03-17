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
    screenWidth = 1080;
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
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        std::cout << "Init Error: " << IMG_GetError() << std::endl;
    }
    
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
    
    //Defines the camera size
    screen.x = 0;
    screen.y = 0;
    screen.w = screenWidth;
    screen.h = screenHeight;
    
}

void MainGame::gameLoop(){
    Map firstlevel = *new Map("Images/map.bmp");
    character.getCurrentMapInfo(firstlevel);
    character.init("Images/sprite.png", screen, 100, 300, 50, 50);
    
    while(currentState != GameState::EXIT){
        processInput();
        
        SDL_RenderClear(renderer);
        character.render();
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
            /*case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;*/
            case SDL_KEYDOWN:
                switch (evnt.key.keysym.sym) {
                    case SDLK_LEFT:
                        character.move(Movement::LEFT);
                        std::cout << "Left key pressed" << std::endl;
                        break;
                    case SDLK_RIGHT:
                        character.move(Movement::RIGHT);
                        std::cout << "Right key pressed" << std::endl;
                        break;
                    case SDLK_SPACE:
                        character.move(Movement::JUMP);
                        std::cout << "Space pressed" << std::endl;
                        break;
                }
                break;
        }
    }
}
