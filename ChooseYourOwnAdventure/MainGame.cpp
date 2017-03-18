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
#include "Errors.hpp"

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
    character.init("Images/sprite.png", screen, -1.0f, -1.0f, 1.0f, 1.0f);
    gameLoop();
}

void MainGame::initSystems(){
    //Initializes SDL and other packages
    SDL_Init(SDL_INIT_EVERYTHING);
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        std::cout << "Init Error: " << IMG_GetError() << std::endl;
    }
    
    //Creates the window
    window = SDL_CreateWindow("ChooseYourOwnAdventure",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth,
                              screenHeight,
                              SDL_WINDOW_OPENGL);
    
    if(window == nullptr){
        fatalError("SDL Window could not be created.");
    }
    
    //Sets up our OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if(glContext == nullptr){
        fatalError("SDL_GL context could not be created.");
    }
    
    //Tells SDL that we want a double buffered window so we don't
    //have any flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    //Initializes the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //Sets the background color once the screen is flushed
    glClearColor(1.0f, 1.0f, 1.0f, 1.0);
    
    //Defines the camera size
    screen.x = 0;
    screen.y = 0;
    screen.w = screenWidth;
    screen.h = screenHeight;
}

void MainGame::gameLoop(){
    Map firstlevel = *new Map("Images/map.bmp");
    character.getCurrentMapInfo(firstlevel);
    
    while(currentState != GameState::EXIT){
        processInput();
        drawGame();
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

void MainGame::drawGame(){
    //Sets the base depth to 1.0
    glClearDepth(1.0);
    //Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    character.render();
    
    //Swaps the buffer and draw everything to the scrren
    SDL_GL_SwapWindow(window);
}
